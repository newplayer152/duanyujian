#include "threadpool.h"
//线程池构造
ThreadPool::ThreadPool(size_t numThreads) : m_stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {//初始多个线程 并让它们循环等待，任务来了便分配线程去执行，执行完继续等待
        m_workers.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(m_queueMutex);
                    m_condition.wait(lock, [this] { return m_stop || !m_tasks.empty(); });//条件等等
                    if (m_stop && m_tasks.empty()) return;//直到更新停止标志或任务队列为空跳出循环
                    task = std::move(m_tasks.front());//取出任务
                    m_tasks.pop();//删除任务
                }
                task();//执行任务
            }
        });
    }
}
//析构线程池
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_stop = true;//更新停止标志位
    }
    m_condition.notify_all();//唤醒所有线程
    for (std::thread& worker : m_workers) worker.join();//等待线程结束
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_tasks.push(std::move(task));//发布任务
    }
    m_condition.notify_one();//唤醒一个线程
}