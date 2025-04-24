#include "mysharedptr.h"

// ���캯������ʼ��ָ��
template <typename T>
MySharedPtr<T>::MySharedPtr(T* ptr) : myBasePtr(ptr), ref_count(new int(1)), mtx(new std::mutex()) {}

// �������캯����ʵ�ֹ�������Ȩ
template <typename T>
MySharedPtr<T>::MySharedPtr(const MySharedPtr<T>& sp) {
    myBasePtr = sp.myBasePtr;
    ref_count = sp.ref_count;
    mtx = sp.mtx;
    if (ref_count) {
        std::lock_guard<std::mutex> lock(*mtx);
        ++(*ref_count);   // �������ü���
    }
}


// �ƶ����캯����ת������Ȩ
template <typename T>
MySharedPtr<T>::MySharedPtr(MySharedPtr<T>&& sp) noexcept {
    myBasePtr = sp.myBasePtr;
    ref_count = sp.ref_count;
    mtx = sp.mtx;

    // ��� other ָ�룬�����ظ��ͷ�
    sp.myBasePtr = nullptr;
    sp.ref_count = nullptr;
    sp.mtx = nullptr;
}

// ��ֵ��������������ֵ��
template <typename T>
MySharedPtr<T>& MySharedPtr<T>:: operator=(const MySharedPtr<T>& sp) {
    if (this != &sp) {
        release();  // �ͷ�ԭ�ж���
        myBasePtr = sp.myBasePtr;
        ref_count = sp.ref_count;
        mtx = sp.mtx;

        if (ref_count) {
            std::lock_guard<std::mutex> lock(*mtx);
            ++(*ref_count);  // �������ü���
        }
    }
    return *this;
}

// ��ֵ���������ƶ���ֵ��
template <typename T>
MySharedPtr<T>& MySharedPtr<T>:: operator=(MySharedPtr<T>&& sp) noexcept {
    if (this != &sp) {
        release();  // �ͷ�ԭ�ж���

        myBasePtr = sp.myBasePtr;
        ref_count = sp.ref_count;
        mtx = sp.mtx;

        // ��� other ָ�룬�����ظ��ͷ�
        sp.myBasePtr = nullptr;
        sp.ref_count = nullptr;
        sp.mtx = nullptr;
    }
    return *this;
}

// �����ò�����
template <typename T>
T& MySharedPtr<T>:: operator*() const {//*p��ʹ��ʱ��ʾ����
    return *myBasePtr;
}

// ��ͷ������
template <typename T>
T* MySharedPtr<T>:: operator->() const {
    return myBasePtr;
}

// ��ȡԭʼָ��
template <typename T>
T* MySharedPtr<T>::get() const {
    return myBasePtr;
}

// ���ص�ǰ�����ü���
template <typename T>
int MySharedPtr<T>::useCount() const {
    if (ref_count) {
        std::lock_guard<std::mutex> lock(*mtx);
        return *ref_count;
    }
    return 0;
}

// ���ù���Ķ���
template <typename T>
void MySharedPtr<T>::reset(T* ptr) {
    release();  // �ͷŵ�ǰ�Ķ���
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

// �����������ͷ���Դ
template <typename T>
MySharedPtr<T>::~MySharedPtr() {
    release();  // ����������ʱ���ͷ���Դ
}

template<typename T>
void MySharedPtr<T>::release()
{
    
    if (ref_count) {
        //std::lock_guard<std::mutex> lock(*mtx);
        if (--(*ref_count) == 0) {   // ���ü�����Ϊ0���ͷ��ڴ�
            delete myBasePtr;
            delete ref_count;
            delete mtx;
            myBasePtr = nullptr;
            ref_count = nullptr;
            mtx = nullptr;
        }
    }
    
}

template class MySharedPtr<Base>;//����ʽʵ��������߱�����Ϊ Base �������� MySharedPtr �����г�Ա�������������캯��
