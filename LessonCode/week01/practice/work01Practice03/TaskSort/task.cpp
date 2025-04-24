#include<iostream>
#include"task.h"


// 构造函数  
Task::Task(const std::string& name, int duration, int priority)
    : m_name(name), m_duration(duration), m_priority(priority) {};

// 拷贝构造函数
Task::Task(const Task& other) :
    m_name(other.m_name), m_duration(other.m_duration), m_priority(other.m_priority) {};

// 拷贝赋值运算符
Task& Task::operator=(const Task& other) {
    if (this != &other) {
        m_name = other.m_name;
        m_duration = other.m_duration;
        m_priority = other.m_priority;
    }
    return *this;
}

// 析构函数
Task::~Task() {};

// 移动构造函数
Task::Task(Task&& other) noexcept : m_name(other.m_name), m_duration(other.m_duration), m_priority(other.m_priority) {
    other.m_name =""; // 避免悬空引用
    other.m_duration = 0;
    other.m_priority = 0;
}

// 移动赋值运算符
Task& Task::operator=(Task&& other) noexcept {
    if (this != &other) {
        m_name = other.m_name;
        m_duration = other.m_duration;
        m_priority = other.m_priority;

        other.m_name = ""; // 避免悬空引用
        other.m_duration = 0;
        other.m_priority = 0;
    }
    return *this;
}


// getXXX 方法  
std::string Task:: getName() const { return m_name; }
int Task:: getDuration()const { return m_duration; }
int Task:: getPriority() const { return m_priority; }

