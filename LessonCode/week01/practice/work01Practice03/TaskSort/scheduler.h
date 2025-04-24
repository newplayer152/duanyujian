#ifndef __TASKSORT_SCHEDULER_H__  
#define __TASKSORT_SCHEDULER_H__
#include<iostream>
#include"task.h"
#include<vector>
#include <algorithm>
#include"taskcompartor.h"
class Scheduler {
public:

    //���캯��
    Scheduler();

    

    // �������캯��
    Scheduler(const Scheduler& other);
    // ������ֵ�����
    Scheduler& operator=(const Scheduler& other);

    // ��������
    ~Scheduler();

    // �ƶ����캯��
    Scheduler(Scheduler&& other) noexcept;

    // �ƶ���ֵ�����
    Scheduler& operator=(Scheduler&& other) noexcept;

    // �������  
    void addTask(const Task& task);

    // �������������  
    void sortTasks();

    // �������  
    void printTasks() const;
    
    const std::vector<Task>&  getTask()const;
private:
    std::vector<Task> m_tasks;

};

#endif //__TASKSORT_SCHEDULER_H__
