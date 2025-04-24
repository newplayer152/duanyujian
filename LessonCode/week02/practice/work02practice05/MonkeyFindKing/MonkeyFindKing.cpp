#include <iostream>

template <class T>
class __list_node
{
public:
    typedef __list_node* node_pointer;
    node_pointer prev;
    node_pointer next;
    T data;

    // 构造函数初始化节点
    __list_node(T value) : prev(nullptr), next(nullptr), data(value) {}
};

// 创建一个环状双向链表，并按规则报数，直到剩下一只猴子
template <class T>
class CircularList
{
private:
    typedef __list_node<T>* node_pointer;
    node_pointer head; // 头节点

public:
    CircularList() : head(nullptr) {}

    // 析构函数
    ~CircularList() {
        if (head) {
            node_pointer temp = head;
            do {
                node_pointer next = temp->next;
                delete temp;
                temp = next;
            } while (temp != head);
        }
    }

    // 添加节点到链表
    void append(T value) {
        node_pointer newNode = new __list_node<T>(value);
        if (!head) {
            head = newNode;
            head->next = head;
            head->prev = head;
        }
        else {
            node_pointer tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
    }

    // 解决猴子问题，按顺序输出退出的猴子的编号
    void findMonkeyKing(int m) {
        node_pointer current = head;

        while (current->next != current) { // 当链表中还有超过1个节点时
            // 报数m次，移动m-1次
            for (int i = 1; i < m; ++i) {
                current = current->next;
            }
            // 输出当前退出的猴子
            std::cout << current->data << " ";

            // 从链表中移除当前节点
            node_pointer prevNode = current->prev;
            node_pointer nextNode = current->next;

            prevNode->next = nextNode;
            nextNode->prev = prevNode;

            if (current == head) {
                head = nextNode;
            }
            delete current;
            current = nextNode; // 继续从下一个节点开始报数
        }
        // 输出最后的猴王
        std::cout << current->data << std::endl;
    }
};

int main() {
    int n, m;
    std::cout << "请输入猴子的总数n和报数的上限m：";
    std::cin >> n >> m;

    CircularList<int> monkeyCircle;

    // 初始化猴子编号
    for (int i = 1; i <= n; ++i) {
        monkeyCircle.append(i);
    }

    // 开始猴子选王游戏，输出退出的猴子和最后的猴王
    monkeyCircle.findMonkeyKing(m);

    return 0;
}
