#ifndef __TASKSORT_TASKCOMPARTOR_H__  
#define __TASKSORT_TASKCOMPARTOR_H__

#include<iostream>
#include"task.h"

class TaskCompartor {
public:

    //���캯��
    TaskCompartor();

    // �������캯��
    TaskCompartor(const TaskCompartor& other);
    // ������ֵ�����
    TaskCompartor& operator=(const TaskCompartor& other);

    // ��������
    ~TaskCompartor();

    // �ƶ����캯��
    TaskCompartor(TaskCompartor&& other) noexcept;

    // �ƶ���ֵ�����
    TaskCompartor& operator=(TaskCompartor&& other) noexcept;


    bool operator()(Task& t1, Task& t2);

};
#endif //__TASKSORT_TASKCOMPARTOR_H__

