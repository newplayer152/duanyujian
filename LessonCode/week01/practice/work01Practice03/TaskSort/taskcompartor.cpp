
#include<iostream>
#include"task.h"
#include"taskcompartor.h"


// ���캯��
TaskCompartor::TaskCompartor(){}

// �������캯��
TaskCompartor::TaskCompartor(const TaskCompartor& other){}

// ������ֵ�����
TaskCompartor& TaskCompartor::operator=(const TaskCompartor& other)
{
    return *this;
}

// ��������
TaskCompartor::~TaskCompartor(){}

// �ƶ����캯��
TaskCompartor::TaskCompartor(TaskCompartor&& other) noexcept{}

// �ƶ���ֵ�����
TaskCompartor& TaskCompartor::operator=(TaskCompartor&& other) noexcept
{
    return *this;
}

bool TaskCompartor::operator()(Task& t1, Task& t2) {
    if (t1.getPriority() != t2.getPriority()) {
        return t1.getPriority() > t2.getPriority(); // ���ȼ��ߵ���������  
    }
    else {
        return t1.getDuration() < t2.getDuration(); // ���ȼ���ͬ�����ʱ��̵���������  
    }
}


