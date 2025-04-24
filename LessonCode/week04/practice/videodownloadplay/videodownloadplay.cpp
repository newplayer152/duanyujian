#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <chrono>
#include <atomic>

std::atomic<size_t> videoData(0);
std::atomic<size_t> videoAllData(1000);
std::mutex print_mutex;
std::condition_variable cond_var;

void safe_print(const std::string& msg)
{
    std::lock_guard<std::mutex> guard(print_mutex);
    std::cout << msg << std::endl;
}

void downloadVideo()
{
    while (videoAllData > 0) // 直接使用原子变量检查
    {
        // 等待 videoData 为 0 时才能下载新的段
        {
            std::unique_lock<std::mutex> lock(print_mutex); // 仅用于条件等待
            cond_var.wait(lock, [] { return videoData.load() == 0; });
        }

        // 模拟下载过程
        safe_print("视频段正在下载...");
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        // 更新下载的数据
        videoData = 100;
        safe_print("视频段100下载完毕");

        cond_var.notify_all(); // 通知消费者线程
    }
}

void videoPlay()
{
    while (videoAllData > 0) // 直接使用原子变量检查
    {
        // 等待 videoData 为 100 时才能播放
        {
            std::unique_lock<std::mutex> lock(print_mutex); // 仅用于条件等待
            cond_var.wait(lock, [] { return videoData.load() == 100; });
        }

        // 模拟播放视频段
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟播放延迟
        videoData -= 50;
        videoAllData -= 50;
        safe_print("播放了 50 数据的段");

        if (videoAllData > 0) // 继续播放剩余的 50 数据
        {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟播放延迟
            videoData -= 50;
            videoAllData -= 50;
            safe_print("播放完一段，等待下载新段");
        }

        cond_var.notify_all(); // 通知下载线程
    }
}




int main()
{
    std::thread t2(downloadVideo);
    std::thread t3(videoPlay);

    t2.join();
    t3.join();
    safe_print("播放完毕");
    return 0;
}
