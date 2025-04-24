#ifndef __TASKSORT_SCHEDULER_H__  
#define __TASKSORT_SCHEDULER_H__
#include<iostream>
#include"task.h"
#include<vector>
#include <algorithm>
#include"taskcompartor.h"
class Scheduler {
public:

    //构造函数
    Scheduler();

    

    // 拷贝构造函数
    Scheduler(const Scheduler& other);
    // 拷贝赋值运算符
    Scheduler& operator=(const Scheduler& other);

    // 析构函数
    ~Scheduler();

    // 移动构造函数
    Scheduler(Scheduler&& other) noexcept;

    // 移动赋值运算符
    Scheduler& operator=(Scheduler&& other) noexcept;

    // 添加任务  
    void addTask(const Task& task);

    // 对任务进行排序  
    void sortTasks();

    // 输出任务  
    void printTasks() const;
    
    const std::vector<Task>&  getTask()const;
private:
    std::vector<Task> m_tasks;

};

#endif //__TASKSORT_SCHEDULER_H__
