#include <benchmark/benchmark.h>
#include "keywordsearcher.h"
int keywordSearchFunction() {
    try {
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
    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

static void BM_KeywordSearchFunction(benchmark::State& state) {
    for (auto _ : state) {
        keywordSearchFunction();  // 测试代码
    }
}
BENCHMARK(BM_KeywordSearchFunction)->Threads(4)->Threads(8)->Threads(12);  // 注册基准测试

BENCHMARK_MAIN();