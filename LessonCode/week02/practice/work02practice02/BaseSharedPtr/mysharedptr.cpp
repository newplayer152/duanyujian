#include "mysharedptr.h"

// 构造函数，初始化指针
template <typename T>
MySharedPtr<T>::MySharedPtr(T* ptr) : myBasePtr(ptr), ref_count(new int(1)), mtx(new std::mutex()) {}

// 拷贝构造函数，实现共享所有权
template <typename T>
MySharedPtr<T>::MySharedPtr(const MySharedPtr<T>& sp) {
    myBasePtr = sp.myBasePtr;
    ref_count = sp.ref_count;
    mtx = sp.mtx;
    if (ref_count) {
        std::lock_guard<std::mutex> lock(*mtx);
        ++(*ref_count);   // 增加引用计数
    }
}


// 移动构造函数，转移所有权
template <typename T>
MySharedPtr<T>::MySharedPtr(MySharedPtr<T>&& sp) noexcept {
    myBasePtr = sp.myBasePtr;
    ref_count = sp.ref_count;
    mtx = sp.mtx;

    // 清空 other 指针，避免重复释放
    sp.myBasePtr = nullptr;
    sp.ref_count = nullptr;
    sp.mtx = nullptr;
}

// 赋值操作符（拷贝赋值）
template <typename T>
MySharedPtr<T>& MySharedPtr<T>:: operator=(const MySharedPtr<T>& sp) {
    if (this != &sp) {
        release();  // 释放原有对象
        myBasePtr = sp.myBasePtr;
        ref_count = sp.ref_count;
        mtx = sp.mtx;

        if (ref_count) {
            std::lock_guard<std::mutex> lock(*mtx);
            ++(*ref_count);  // 增加引用计数
        }
    }
    return *this;
}

// 赋值操作符（移动赋值）
template <typename T>
MySharedPtr<T>& MySharedPtr<T>:: operator=(MySharedPtr<T>&& sp) noexcept {
    if (this != &sp) {
        release();  // 释放原有对象

        myBasePtr = sp.myBasePtr;
        ref_count = sp.ref_count;
        mtx = sp.mtx;

        // 清空 other 指针，避免重复释放
        sp.myBasePtr = nullptr;
        sp.ref_count = nullptr;
        sp.mtx = nullptr;
    }
    return *this;
}

// 解引用操作符
template <typename T>
T& MySharedPtr<T>:: operator*() const {//*p在使用时表示引用
    return *myBasePtr;
}

// 箭头操作符
template <typename T>
T* MySharedPtr<T>:: operator->() const {
    return myBasePtr;
}

// 获取原始指针
template <typename T>
T* MySharedPtr<T>::get() const {
    return myBasePtr;
}

// 返回当前的引用计数
template <typename T>
int MySharedPtr<T>::useCount() const {
    if (ref_count) {
        std::lock_guard<std::mutex> lock(*mtx);
        return *ref_count;
    }
    return 0;
}

// 重置管理的对象
template <typename T>
void MySharedPtr<T>::reset(T* ptr) {
    release();  // 释放当前的对象
    if (ptr) {
        myBasePtr = ptr;
        ref_count = new int(1);
        mtx = new std::mutex();
    }
    else {
        myBasePtr = nullptr;
        ref_count = nullptr;
        mtx = nullptr;
    }
}

// 析构函数，释放资源
template <typename T>
MySharedPtr<T>::~MySharedPtr() {
    release();  // 当对象销毁时，释放资源
}

template<typename T>
void MySharedPtr<T>::release()
{
    
    if (ref_count) {
        //std::lock_guard<std::mutex> lock(*mtx);
        if (--(*ref_count) == 0) {   // 引用计数减为0，释放内存
            delete myBasePtr;
            delete ref_count;
            delete mtx;
            myBasePtr = nullptr;
            ref_count = nullptr;
            mtx = nullptr;
        }
    }
    
}

template class MySharedPtr<Base>;//此显式实例化会告诉编译器为 Base 类型生成 MySharedPtr 的所有成员函数，包括构造函数
