#pragma once
#include<mutex>
#include "base.h"
template <typename T>
class MySharedPtr
{
public:

    // 构造函数，初始化指针
    MySharedPtr(T* ptr = nullptr);

    // 拷贝构造函数，实现共享所有权
    MySharedPtr(const MySharedPtr<T>& sp);

    // 移动构造函数，转移所有权
    MySharedPtr(MySharedPtr<T>&& sp) noexcept;

    // 赋值操作符（拷贝赋值）
    MySharedPtr<T>& operator=(const MySharedPtr<T>& sp);

    // 赋值操作符（移动赋值）
    MySharedPtr<T>& operator=(MySharedPtr<T>&& sp) noexcept;

    // 解引用操作符
    T& operator*() const;

    // 箭头操作符
    T* operator->() const;

    // 获取原始指针
    T* get() const;

    // 返回当前的引用计数
    int useCount() const;

    // 重置管理的对象
    void reset(T* ptr = nullptr);

    // 析构函数，释放资源
    ~MySharedPtr();

private:
    //用户自定义
    T* myBasePtr;
    int* ref_count;
    std::mutex* mtx;//互斥锁
    // 辅助函数，用于释放资源
    void release();
};


