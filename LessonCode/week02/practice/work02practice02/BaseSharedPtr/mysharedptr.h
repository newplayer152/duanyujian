#pragma once
#include<mutex>
#include "base.h"
template <typename T>
class MySharedPtr
{
public:

    // ���캯������ʼ��ָ��
    MySharedPtr(T* ptr = nullptr);

    // �������캯����ʵ�ֹ�������Ȩ
    MySharedPtr(const MySharedPtr<T>& sp);

    // �ƶ����캯����ת������Ȩ
    MySharedPtr(MySharedPtr<T>&& sp) noexcept;

    // ��ֵ��������������ֵ��
    MySharedPtr<T>& operator=(const MySharedPtr<T>& sp);

    // ��ֵ���������ƶ���ֵ��
    MySharedPtr<T>& operator=(MySharedPtr<T>&& sp) noexcept;

    // �����ò�����
    T& operator*() const;

    // ��ͷ������
    T* operator->() const;

    // ��ȡԭʼָ��
    T* get() const;

    // ���ص�ǰ�����ü���
    int useCount() const;

    // ���ù���Ķ���
    void reset(T* ptr = nullptr);

    // �����������ͷ���Դ
    ~MySharedPtr();

private:
    //�û��Զ���
    T* myBasePtr;
    int* ref_count;
    std::mutex* mtx;//������
    // ���������������ͷ���Դ
    void release();
};


