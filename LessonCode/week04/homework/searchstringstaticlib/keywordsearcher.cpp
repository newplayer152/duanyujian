#include "keywordsearcher.h"
// KeywordSearcher构造函数和方法实现
KeywordSearcher::KeywordSearcher(const std::string& filepath, const std::string& keywordFile)
    : m_filepath(filepath), m_threadPool(std::thread::hardware_concurrency()), //获取当前电脑cpu线程数
        m_memoryPool(), m_fileData(nullptr), m_fileSize(0) {
    loadKeywords(keywordFile);
    mapFileToMemory();
}

KeywordSearcher::~KeywordSearcher()
{
    if (m_fileData) {//移除映射
        UnmapViewOfFile(m_fileData);
    }
}
//加载关键字
void KeywordSearcher::loadKeywords(const std::string& keywordFile) {
    std::ifstream file(keywordFile);
    std::string keyword;
    while (std::getline(file, keyword)) {
        if (!keyword.empty()) {
            m_keywords.push_back(keyword);
        }
    }
}
//文件映射
void KeywordSearcher::mapFileToMemory() {
    HANDLE hFile = CreateFileA(m_filepath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Failed to open file.");
    }

    LARGE_INTEGER fileSizeLarge;
    if (!GetFileSizeEx(hFile, &fileSizeLarge)) {
        CloseHandle(hFile);
        throw std::runtime_error("Failed to get file size.");
    }

    m_fileSize = static_cast<size_t>(fileSizeLarge.QuadPart);

    HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMap == NULL) {
        CloseHandle(hFile);
        throw std::runtime_error("Failed to create file mapping.");
    }

    m_fileData = static_cast<char*>(MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0));
    if (m_fileData == NULL) {
        CloseHandle(hMap);
        CloseHandle(hFile);
        throw std::runtime_error("Failed to map view of file.");
    }

    CloseHandle(hMap);
    CloseHandle(hFile);
}
//搜索函数
void KeywordSearcher::search() {
    // 多线程任务分配
    for (const auto& keyword : m_keywords) {
        auto start = std::chrono::high_resolution_clock::now();//开始计时
        // 使用 Boyer-Moore-Horspool 搜索器 获取坏字符表
        auto  badCharTable = std::boyer_moore_horspool_searcher(keyword.begin(), keyword.end());
        KeywordResult result{ keyword, 0, 0.0 };
        size_t numTasks = max(std::thread::hardware_concurrency(), 4);
        if (keyword.size() > 50) {//当关键字较长时 push_back数量也相对较少 可以降低块大小、增加任务数量 充分利用线程池
            numTasks = numTasks * 30;
        }
        size_t chunkSize = m_fileSize / numTasks;
        size_t overlapSize = keyword.size() - 1;

        // 创建局部计数器减少锁竞争
        std::vector<std::future<size_t>> positionCountFutures;//位置计数
        std::vector<std::future<size_t*>> positionPointerstFutures;// 记录匹配位置容器首地址

        size_t startIdx;//文件块开始位置
        size_t endIdx;//文件块结束位置

        for (size_t i = 0; i < numTasks; ++i) {
            startIdx = i * chunkSize;
            //边界处理 防止关键字被截断漏检或复检
            endIdx = (i == numTasks - 1) ? m_fileSize : min(m_fileSize, (i + 1) * chunkSize + overlapSize);

            // 创建 promise-future 对，用于捕获线程池任务的结果
            auto positionCountPromise = std::make_shared<std::promise<size_t>>();
            positionCountFutures.push_back(positionCountPromise->get_future());

            auto positionPointersPromise = std::make_shared<std::promise<size_t*>>();
            positionPointerstFutures.push_back(positionPointersPromise->get_future());

            // 将任务提交到线程池
            m_threadPool.enqueue([this, keyword, startIdx, endIdx, positionCountPromise, positionPointersPromise, badCharTable]() {
                size_t* posIdx = m_memoryPool.allocate(100); //从内存池中预先分配位置预先分配100个位置
                size_t posCount = 0;
                if (keyword.size() > 50) {//关键字过长时选择Boyer-Moore-Horspool 搜索算法更快
                    searchKeywordBoyerMooreHorspool(keyword, startIdx, endIdx, posIdx, posCount, badCharTable);
                }
                else {
                    countKeywordInBlock(keyword, startIdx, endIdx, posIdx, posCount);
                }
                positionCountPromise->set_value(posCount); // 返回块内下标数量
                positionPointersPromise->set_value(posIdx);// 返回块内的匹配位置容器首地址
                });
        }
        // 汇总局部计数
        std::vector<size_t> positionCounts; // 用于保存 posCount
        for (size_t i = 0; i < positionCountFutures.size(); ++i) {
            size_t posCount = positionCountFutures[i].get();
            result.m_count += posCount;//汇总计数
            positionCounts.push_back(posCount);
        }
        result.m_positionIndexs.reserve(result.m_count); // 预分配

        // 收集所有位置下标，使用保存的 positionPointerstFutures
        for (size_t i = 0; i < positionPointerstFutures.size(); ++i) {
            size_t posCount = positionCounts[i];
            size_t* positions = positionPointerstFutures[i].get();//获取位置的指针
            result.m_positionIndexs.insert(result.m_positionIndexs.end(), positions, positions + posCount);
        }

        auto end = std::chrono::high_resolution_clock::now();//结束计时
        result.m_searchTime = std::chrono::duration<double>(end - start).count();
        std::lock_guard<std::mutex> lock(m_resultMutex);
        m_results[keyword] = std::move(result);//存入结果

        // 重置内存池以供下一次使用
        m_memoryPool.reset();
    }
}



//短关键字符匹配方案
void KeywordSearcher::countKeywordInBlock(const std::string& keyword, size_t startIdx, size_t endIdx,
    size_t*& posIdx, size_t& posCount) {
    size_t pos = 0;
    size_t capacity = 100; // 初始容量

    // 使用 std::string_view 创建内存视图，不进行数据拷贝
    std::string_view buffer(m_fileData + startIdx, endIdx - startIdx);

    // 在内存视图中查找关键字
    while ((pos = buffer.find(keyword, pos)) != std::string_view::npos) {
        // 记录匹配位置并增加计数
        if (posCount >= capacity) {// 扩容
            size_t* newPosIdx = m_memoryPool.allocate(capacity * 2);
            std::copy(posIdx, posIdx + capacity, newPosIdx);
            posIdx = newPosIdx;
            capacity *= 2;
        }
        // 记录匹配位置并增加计数
        posIdx[posCount++] = startIdx + pos;
        pos += keyword.size(); // 移动到下一个位置
    }
}

//长关键字符匹配方案:优化的 Boyer-Moore-Horspool 搜索算法
void KeywordSearcher::searchKeywordBoyerMooreHorspool(const std::string& keyword, size_t startIdx, size_t endIdx,
    size_t*& posIdx, size_t& posCount, const BadCharTable& badCharTable) {
    size_t m = keyword.size();
    posCount = 0;
    size_t capacity = 100; // 初始容量

    // 使用 std::string_view 创建内存视图，不进行数据拷贝
    std::string_view buffer(m_fileData + startIdx, endIdx - startIdx);
    auto pos = std::search(buffer.begin(), buffer.end(), badCharTable);

    while (pos != buffer.end()) {
        // 计算匹配的位置
        size_t foundPos = std::distance(buffer.begin(), pos);

        if (posCount >= capacity) {// 扩容
            size_t* newPosIdx = m_memoryPool.allocate(capacity * 2);
            std::copy(posIdx, posIdx + capacity, newPosIdx);
            posIdx = newPosIdx;
            capacity *= 2;
        }
        // 记录匹配位置并增加计数
        posIdx[posCount++] = foundPos + startIdx;

        // 更新下一个查找位置，从当前匹配位置后继续查找
        pos = std::search(pos + m, buffer.end(), badCharTable);
    }

}
//写入文件
void KeywordSearcher::writeResults(const std::string& outputFile) {
    std::ofstream output(outputFile);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open output file.");
    }

    for (const auto& entry : m_results) {
        const KeywordResult& result = entry.second;
        int time_in_ms = static_cast<int>(result.m_searchTime * 1000);
        output << result.m_keyword << "     count:" << result.m_count << "  time:" << time_in_ms << "ms\n";
    }
}
//获取搜索结果
std::unordered_map<std::string, KeywordResult> KeywordSearcher::getResults()
{
    return m_results;
}
