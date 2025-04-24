#ifndef __SEARCHSTRING_KEYWORDSEARCHER_H
#define __SEARCHSTRING_KEYWORDSEARCHER_H
#include "keywordresult.h"
#include "threadpool.h"
#include "memorypool.h"
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <chrono>
#include <future>
#include <windows.h>
#include <queue>
#include <string_view>

//接受坏字符表
using BadCharTable = std::boyer_moore_horspool_searcher<std::string::const_iterator>;


// 主搜索类
class KeywordSearcher {
public:
    //搜索类初始化、析构
    KeywordSearcher(const std::string& filepath, const std::string& keywordFile);
    ~KeywordSearcher();
    //搜索函数
    void search();
    //写入结果函数
    void writeResults(const std::string& outputFile);
    //获取结果函数
    std::unordered_map<std::string, KeywordResult> getResults();
private:
    //文件映射
    void mapFileToMemory();
    //加载待搜索关键字
    void loadKeywords(const std::string& keywordFile);
    //短关键字符匹配方案
    void countKeywordInBlock(const std::string& keyword, size_t startIdx, size_t endIdx, size_t*& posIdx, size_t& posCount);
    //长关键字符匹配方案
    void searchKeywordBoyerMooreHorspool(const std::string& keyword, size_t startIdx, size_t endIdx,
        size_t*& posIdx, size_t& posCount, const BadCharTable& badCharTable);

    std::string m_filepath;//文件路径
    std::vector<std::string> m_keywords;//待搜索关键字
    std::unordered_map<std::string, KeywordResult> m_results;//存储结果
    ThreadPool m_threadPool;//线程池
    MemoryPool m_memoryPool;//内存池
    std::mutex m_resultMutex;//为写入结果时加锁
    char* m_fileData;//映射首地址
    size_t m_fileSize;//文件大小
    
};

#endif//__SEARCHSTRING_KEYWORDSEARCHER_H
