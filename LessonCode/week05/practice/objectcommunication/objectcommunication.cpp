#include <iostream>
#include <functional>

// 定义 Show 类
class Show {
public:
    void function() {
        std::cout << "Show::function 被调用了！" << std::endl;
    }
};

// 定义 Button 类
class Button {
public:
    // click 方法
    void click() {
        if (callback) {
            callback(); // 调用 Show 中的 function 函数
        }
        else {
            std::cout << "没有绑定回调函数！" << std::endl;
        }
    }

    // 设置回调函数
    void setCallback(std::function<void()> func) {
        callback = func;
    }

private:
    std::function<void()> callback; // 保存回调函数
};

int main() {
    Show showObj;
    Button buttonObj;

    // 将 Show::function 绑定到 Button 的回调函数中
    buttonObj.setCallback(std::bind(&Show::function, &showObj));

    // 调用 Button 的 click 方法，自动调用 Show 的 function 方法
    buttonObj.click();

    return 0;
}
