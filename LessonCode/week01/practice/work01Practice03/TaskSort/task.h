#ifndef __TASKSORT_TASK_H__  
#define __TASKSORT_TASK_H__
#include <iostream>

class Task {
public:

    //���캯��
    Task(const std::string& name, int duration, int priority);

    // �������캯��
    Task(const Task& other);
    // ������ֵ�����
    Task& operator=(const Task& other);

    // ��������
    ~Task();

    // �ƶ����캯��
    Task(Task&& other) noexcept;

    // �ƶ���ֵ�����
    Task& operator=(Task&& other) noexcept;

    // getXXX ����  
    std::string getName()const;
    int getDuration()const;
    int getPriority()const;
private:
	std::string m_name;
	int m_duration;
	int m_priority;

};
#endif //__TASKSORT_TASK_H__

