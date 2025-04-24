#ifndef __TASKSORT_TASK_H__  
#define __TASKSORT_TASK_H__
#include <iostream>

class Task {
public:

    //构造函数
    Task(const std::string& name, int duration, int priority);

    // 拷贝构造函数
    Task(const Task& other);
    // 拷贝赋值运算符
    Task& operator=(const Task& other);

    // 析构函数
    ~Task();

    // 移动构造函数
    Task(Task&& other) noexcept;

    // 移动赋值运算符
    Task& operator=(Task&& other) noexcept;

    // getXXX 方法  
    std::string getName()const;
    int getDuration()const;
    int getPriority()const;
private:
	std::string m_name;
	int m_duration;
	int m_priority;

};
#endif //__TASKSORT_TASK_H__

