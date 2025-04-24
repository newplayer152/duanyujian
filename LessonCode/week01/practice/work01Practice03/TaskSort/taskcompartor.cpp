
#include<iostream>
#include"task.h"
#include"taskcompartor.h"


// 构造函数
TaskCompartor::TaskCompartor(){}

// 拷贝构造函数
TaskCompartor::TaskCompartor(const TaskCompartor& other){}

// 拷贝赋值运算符
TaskCompartor& TaskCompartor::operator=(const TaskCompartor& other)
{
    return *this;
}

// 析构函数
TaskCompartor::~TaskCompartor(){}

// 移动构造函数
TaskCompartor::TaskCompartor(TaskCompartor&& other) noexcept{}

// 移动赋值运算符
TaskCompartor& TaskCompartor::operator=(TaskCompartor&& other) noexcept
{
    return *this;
}

bool TaskCompartor::operator()(Task& t1, Task& t2) {
    if (t1.getPriority() != t2.getPriority()) {
        return t1.getPriority() > t2.getPriority(); // 优先级高的任务优先  
    }
    else {
        return t1.getDuration() < t2.getDuration(); // 优先级相同则持续时间短的任务优先  
    }
}


