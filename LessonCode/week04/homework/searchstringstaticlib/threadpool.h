#ifndef __SEARCHSTRING_THREADPOOL_H
#define __SEARCHSTRING_THREADPOOL_H
#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <queue>
class ThreadPool
{
public:
    //初始化线程池内线程数
    ThreadPool(size_t numThreads);
    ~ThreadPool();
    //给线程分配任务
    void enqueue(std::function<void()> task);

private:
    std::vector<std::thread> m_workers;//存储线程
    std::queue<std::function<void()>> m_tasks;//任务队列
    std::mutex m_queueMutex;//用于加锁保护对线程池的异步操作
    std::condition_variable m_condition;//条件
    bool m_stop;//线程池停止标志
};
#endif//__SEARCHSTRING_THREADPOOL_H
