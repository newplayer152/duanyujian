#include "memorypool.h"

// 内存池构造
MemoryPool::MemoryPool(size_t blockSize)
    : m_blockSize(blockSize), m_currentBlockSize(blockSize), m_currentOffset(0), m_currentBlock(nullptr)
{
    // 预先分配一个块
    m_currentBlock = new char[m_blockSize];
    m_blocks.push_back(m_currentBlock);
}

MemoryPool::~MemoryPool()
{
    // 释放所有块
    for (auto block : m_blocks)
    {
        delete[] block;
    }
}

//分配内存
size_t* MemoryPool::allocate(size_t numElements)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    size_t sizeNeeded = numElements * sizeof(size_t); // 所需大小

    if (m_currentOffset + sizeNeeded > m_currentBlockSize) // 当前块是否有足够空间
    {
        if (sizeNeeded > m_currentBlockSize) {//需要的空间太多就扩展块
            m_currentBlockSize *= 2;
        }
        try {// 分配新的块
            m_currentBlock = new char[m_currentBlockSize];
            m_blocks.push_back(m_currentBlock); // 将新块添加到块列表中 方便析构释放
        }
        catch (const std::bad_alloc& e) {//分配失败抛异常
            throw std::runtime_error("Memory allocation failed for m_currentBlock: " + std::string(e.what()));
        }
        m_currentOffset = 0; // 偏移量重置
    }
    size_t* ptr = reinterpret_cast<size_t*>(m_currentBlock + m_currentOffset); // 获取可用地址指针
    m_currentOffset += sizeNeeded; // 更新偏移量
    return ptr;
}

//重置函数
void MemoryPool::reset()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    // 保留第一个块，释放其他块
    if (m_blocks.size() > 1)
    {
        for (size_t i = 1; i < m_blocks.size(); ++i)
        {
            delete[] m_blocks[i];
        }
        m_blocks.resize(1);
    }
    m_currentOffset = 0;
    m_currentBlockSize = m_blockSize;
    m_currentBlock = m_blocks.front();
}