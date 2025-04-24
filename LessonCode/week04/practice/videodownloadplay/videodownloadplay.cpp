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
    while (videoAllData > 0) // ֱ��ʹ��ԭ�ӱ������
    {
        // �ȴ� videoData Ϊ 0 ʱ���������µĶ�
        {
            std::unique_lock<std::mutex> lock(print_mutex); // �����������ȴ�
            cond_var.wait(lock, [] { return videoData.load() == 0; });
        }

        // ģ�����ع���
        safe_print("��Ƶ����������...");
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        // �������ص�����
        videoData = 100;
        safe_print("��Ƶ��100�������");

        cond_var.notify_all(); // ֪ͨ�������߳�
    }
}

void videoPlay()
{
    while (videoAllData > 0) // ֱ��ʹ��ԭ�ӱ������
    {
        // �ȴ� videoData Ϊ 100 ʱ���ܲ���
        {
            std::unique_lock<std::mutex> lock(print_mutex); // �����������ȴ�
            cond_var.wait(lock, [] { return videoData.load() == 100; });
        }

        // ģ�ⲥ����Ƶ��
        std::this_thread::sleep_for(std::chrono::seconds(1)); // ģ�ⲥ���ӳ�
        videoData -= 50;
        videoAllData -= 50;
        safe_print("������ 50 ���ݵĶ�");

        if (videoAllData > 0) // ��������ʣ��� 50 ����
        {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // ģ�ⲥ���ӳ�
            videoData -= 50;
            videoAllData -= 50;
            safe_print("������һ�Σ��ȴ������¶�");
        }

        cond_var.notify_all(); // ֪ͨ�����߳�
    }
}




int main()
{
    std::thread t2(downloadVideo);
    std::thread t3(videoPlay);

    t2.join();
    t3.join();
    safe_print("�������");
    return 0;
}
