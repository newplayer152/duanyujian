#include <gtest/gtest.h>
#include "keywordsearcher.h"

TEST(KeywordSearcherTest, TestKeywordCount) {
    std::string xmlFilePath = "enwiki-20231120-abstract1.xml";
    std::string keywordFilePath = "keyword.txt";
    std::string outputFilePath = "newoutput.txt";

    KeywordSearcher searcher(xmlFilePath, keywordFilePath);//初始化
    searcher.search();//搜索
    auto results = searcher.getResults();//获取结果

    EXPECT_EQ(results["Panda"].m_count, 533);//结果对比测试
    EXPECT_EQ(results["<sublink linktype=\"nav\"><anchor>"].m_count, 6165823);
    EXPECT_EQ(results["<sublink linktype=\"nav\"><anchor>"].m_positionIndexs.size(), 6165823);//存储内容测试
}
