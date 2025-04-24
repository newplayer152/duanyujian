#include<iostream>
#include"task.h"


// ���캯��  
Task::Task(const std::string& name, int duration, int priority)
    : m_name(name), m_duration(duration), m_priority(priority) {};

// �������캯��
Task::Task(const Task& other) :
    m_name(other.m_name), m_duration(other.m_duration), m_priority(other.m_priority) {};

// ������ֵ�����
Task& Task::operator=(const Task& other) {
    if (this != &other) {
        m_name = other.m_name;
        m_duration = other.m_duration;
        m_priority = other.m_priority;
    }
    return *this;
}

// ��������
Task::~Task() {};

// �ƶ����캯��
Task::Task(Task&& other) noexcept : m_name(other.m_name), m_duration(other.m_duration), m_priority(other.m_priority) {
    other.m_name =""; // ������������
    other.m_duration = 0;
    other.m_priority = 0;
}

// �ƶ���ֵ�����
Task& Task::operator=(Task&& other) noexcept {
    if (this != &other) {
        m_name = other.m_name;
        m_duration = other.m_duration;
        m_priority = other.m_priority;

        other.m_name = ""; // ������������
        other.m_duration = 0;
        other.m_priority = 0;
    }
    return *this;
}


// getXXX ����  
std::string Task:: getName() const { return m_name; }
int Task:: getDuration()const { return m_duration; }
int Task:: getPriority() const { return m_priority; }

