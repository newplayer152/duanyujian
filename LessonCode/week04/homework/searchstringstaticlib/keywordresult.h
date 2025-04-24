#ifndef __SEARCHSTRING_KEYWORDRESULT_H
#define __SEARCHSTRING_KEYWORDRESULT_H
#include <string>
#include <vector>
// 关键词统计结构
struct KeywordResult
{
    std::string m_keyword;//存储关键字
    size_t m_count;//存储个数
    double m_searchTime;//存储搜索时间
    std::vector<size_t> m_positionIndexs;//存储匹配位置(首字符下标)
};
#endif//__SEARCHSTRING_KEYWORDRESULT_H
