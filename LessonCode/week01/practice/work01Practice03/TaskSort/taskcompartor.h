#ifndef __TASKSORT_TASKCOMPARTOR_H__  
#define __TASKSORT_TASKCOMPARTOR_H__

#include<iostream>
#include"task.h"

class TaskCompartor {
public:

    //构造函数
    TaskCompartor();

    // 拷贝构造函数
    TaskCompartor(const TaskCompartor& other);
    // 拷贝赋值运算符
    TaskCompartor& operator=(const TaskCompartor& other);

    // 析构函数
    ~TaskCompartor();

    // 移动构造函数
    TaskCompartor(TaskCompartor&& other) noexcept;

    // 移动赋值运算符
    TaskCompartor& operator=(TaskCompartor&& other) noexcept;


    bool operator()(Task& t1, Task& t2);

};
#endif //__TASKSORT_TASKCOMPARTOR_H__

