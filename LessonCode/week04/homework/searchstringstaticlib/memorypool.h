#ifndef __SEARCHSTRING_MEMORYPOOL_H
#define __SEARCHSTRING_MEMORYPOOL_H
#include <stdint.h>
#include <vector>
#include <mutex>
// 内存池类，用于管理关键词下标的存储
class MemoryPool
{
public:
    MemoryPool(size_t blockSize = 1024 * 1024 * 8); // 默认块大小为8MB
    ~MemoryPool();
    size_t* allocate(size_t numElements);//分配内存函数
    void reset();//重置内存池

private:
    std::vector<char*> m_blocks;//内存块容器
    size_t m_blockSize;//初始内存块大小
    size_t m_currentOffset;//当前块内偏移量
    size_t m_currentBlockSize;//当前块尺寸
    char* m_currentBlock;//当前块首地址
    std::mutex m_mutex;//用于加锁保护内存池的异步操作
};

#endif//__SEARCHSTRING_MEMORYPOOL_H

