#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

// ���� Observer �ӿڣ���ǿ��չ��
class Observer {
public:
    virtual void update(const std::string& message) = 0; // ����֪ͨ�Ľӿ�
    virtual ~Observer() = default;
};

// Server �࣬��Ϊ���۲���
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
        std::cout << "Server: ����������..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // ģ�������
        notifyObservers("�´�����"); // ����֪ͨ
    }

private:
    std::vector<std::shared_ptr<Observer>> observers; // �۲����б�
};

// Client �࣬��Ϊ�۲���
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

    // ���� 10 �� Client �����������Ϊ�۲���
    for (int i = 1; i <= 10; ++i) {
        auto client = std::make_shared<Client>(i);
        server.addObserver(client);
    }


    // ���������� Server �� getInfo��֪ͨ���й۲���
    server.getInfo();

    return 0;
}
