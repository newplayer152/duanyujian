#include "keywordsearcher.h"

int main() {
    try {
        auto begin = std::chrono::high_resolution_clock::now();//开始总计时

        //相对路径
        std::string xmlFilePath = "enwiki-20231120-abstract1.xml";
        std::string keywordFilePath = "keyword.txt";
        std::string outputFilePath = "newoutput.txt";
        //初始化搜索类
        KeywordSearcher searcher(xmlFilePath, keywordFilePath);
        //开始搜索
        searcher.search();
        //存入结果
        searcher.writeResults(outputFilePath);
        std::cout << "关键词搜索完成，结果已写入 " << outputFilePath << std::endl;
        auto end = std::chrono::high_resolution_clock::now();//结束总计时
        double time = std::chrono::duration<double>(end - begin).count();
        std::cout << "耗时共 " << time << "s" << std::endl;

        // 遍历输出每个关键字存储的下标
        for (const auto& [key, value] : searcher.getResults()) {
            std::cout<<"\"" << key<< "\"  已保存下标(个):  " << value.m_positionIndexs.size() << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}