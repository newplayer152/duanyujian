#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

// 定义 Observer 接口，增强扩展性
class Observer {
public:
    virtual void update(const std::string& message) = 0; // 接收通知的接口
    virtual ~Observer() = default;
};

// Server 类，作为被观察者
class Server {
public:
    void addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void notifyObservers(const std::string& message) {
        for (const auto& observer : observers) {
            if (observer) {
                observer->update(message);
            }
        }
    }

    void getInfo() {
        std::cout << "Server: 检查天气情况..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟检查过程
        notifyObservers("下大暴雨了"); // 发送通知
    }

private:
    std::vector<std::shared_ptr<Observer>> observers; // 观察者列表
};

// Client 类，作为观察者
class Client : public Observer {
public:
    Client(int id) : client_id(id) {}

    void update(const std::string& message) override {
        std::cout << "Client " << client_id << ": " << message << std::endl;
    }

private:
    int client_id;
};



int main() {
    Server server;

    // 创建 10 个 Client 并将它们添加为观察者
    for (int i = 1; i <= 10; ++i) {
        auto client = std::make_shared<Client>(i);
        server.addObserver(client);
    }


    // 主函数调用 Server 的 getInfo，通知所有观察者
    server.getInfo();

    return 0;
}
