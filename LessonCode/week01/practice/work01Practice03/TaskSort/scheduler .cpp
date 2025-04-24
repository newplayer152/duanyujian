#include<iostream>
#include "Scheduler.h"
#include<iostream>
#include"task.h"
#include<vector>
#include <algorithm>
#include"taskcompartor.h"

//���캯��
Scheduler::Scheduler() {};

// �������캯��
Scheduler::Scheduler(const Scheduler& other) {

};

// ������ֵ�����
Scheduler& Scheduler:: operator=(const Scheduler& other) { 
    return *this; 
};

// ��������
Scheduler::~Scheduler() {};

// �ƶ����캯��
Scheduler::Scheduler(Scheduler&& other) noexcept {
};

// �ƶ���ֵ�����
Scheduler& Scheduler:: operator=(Scheduler&& other) noexcept {  
    return *this; 
};


// �������  
void Scheduler::addTask(const Task& task) {
    m_tasks.push_back(task);
}

// �������������  
void Scheduler::sortTasks() {
    std::sort(m_tasks.begin(), m_tasks.end(), TaskCompartor());
}

// �������  
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

