#include<iostream>
#include "Scheduler.h"
#include<iostream>
#include"task.h"
#include<vector>
#include <algorithm>
#include"taskcompartor.h"

//构造函数
Scheduler::Scheduler() {};

// 拷贝构造函数
Scheduler::Scheduler(const Scheduler& other) {

};

// 拷贝赋值运算符
Scheduler& Scheduler:: operator=(const Scheduler& other) { 
    return *this; 
};

// 析构函数
Scheduler::~Scheduler() {};

// 移动构造函数
Scheduler::Scheduler(Scheduler&& other) noexcept {
};

// 移动赋值运算符
Scheduler& Scheduler:: operator=(Scheduler&& other) noexcept {  
    return *this; 
};


// 添加任务  
void Scheduler::addTask(const Task& task) {
    m_tasks.push_back(task);
}

// 对任务进行排序  
void Scheduler::sortTasks() {
    std::sort(m_tasks.begin(), m_tasks.end(), TaskCompartor());
}

// 输出任务  
void Scheduler :: printTasks() const {
    for (const auto& task : m_tasks) {
        std::cout << "Task Name: " << task.getName()
            << ", Duration: " << task.getDuration()
            << ", Priority: " << task.getPriority() << std::endl;
    }
}

const std::vector<Task>& Scheduler::getTask() const
{ 
    return m_tasks;
}

