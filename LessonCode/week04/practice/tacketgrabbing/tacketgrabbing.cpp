#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <condition_variable>

int tickets = 10; // 总票数
std::mutex ticketMutex; // 互斥锁，保护票数
std::condition_variable ticketCond; // 条件变量，用于通知线程

void buyTicket(int userID) {
    while (true) {
        std::unique_lock<std::mutex> lock(ticketMutex); // 加锁，确保线程安全
        if (tickets > 0) {
            // 模拟网络延迟
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "用户 " << userID << " 买票，剩余 " << --tickets << std::endl;

            if (tickets == 0) {
                // 如果票卖完了，通知其他线程
                ticketCond.notify_all();
            }
        }
        else {
            // 如果没有票了，退出循环
            std::cout << "用户 " << userID << " 发现没有票了" << std::endl;
            break;
        }
    }
}

int main() {
    const int userCount = 5; // 模拟5个用户抢票
    std::vector<std::thread> threads;

    // 创建多个线程模拟多个用户抢票
    for (int i = 1; i <= userCount; ++i) {
        threads.push_back(std::thread(buyTicket, i));
    }

    // 等待所有线程执行完毕
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "所有的票卖完了" << std::endl;
    return 0;
}
