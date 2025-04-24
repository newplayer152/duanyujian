#ifndef __LINKLIST_LINKLIST_H
#define __LINKLIST_LINKLIST_H
#include "linklistnode.h"
#include <iostream>

class LinkList {


public:
    // 默认构造函数
    LinkList();

    // 拷贝构造函数
    LinkList(const LinkList& other);

    // 移动构造函数
    LinkList(LinkList&& other) noexcept;

    // 拷贝赋值运算符
    LinkList& operator=(const LinkList& other);

    // 移动赋值运算符
    LinkList& operator=(LinkList&& other) noexcept;

    // 析构函数
    ~LinkList();

    // 插入元素到链表末尾
    void insert(const int& value);

    // 根据位置删除元素
    void remove(size_t index);

    // 更新指定位置的元素
    void update(size_t index, const int& value);

    // 获取指定位置的元素
    int get(size_t index) const;

    // 获取链表大小
    size_t getSize() const;

    // 输出链表内容
    void print() const;
// 清空链表的辅助函数，用于析构和赋值
    void clear();
private:
        LinkListNode* m_head; // 链表头节点指针
        size_t m_size;        // 链表长度

        
};


#endif//__LINKLIST_KQUEUE_H





