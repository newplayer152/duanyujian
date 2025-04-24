#include "linklist.h"

LinkList::LinkList() : m_head(nullptr), m_size(0) {};

LinkList::LinkList(const LinkList& other) : m_head(nullptr), m_size(0) {
    LinkListNode* current = other.m_head;
    while (current) {
        insert(current->getData());
        current = current->next();
    }
}

LinkList::LinkList(LinkList&& other) noexcept : m_head(other.m_head), m_size(other.m_size) {
    other.m_head = nullptr;
    other.m_size = 0;
}

LinkList& LinkList::operator=(const LinkList& other) {
    if (this != &other) {
        clear(); // 清除当前链表数据
        LinkListNode* current = other.m_head;
        while (current) {
            insert(current->getData());
            current = current->next();
        }
    }
    return *this;
}

LinkList& LinkList::operator=(LinkList&& other) noexcept {
    if (this != &other) {
        clear(); // 清除当前链表数据
        m_head = other.m_head;
        m_size = other.m_size;
        other.m_head = nullptr;
        other.m_size = 0;
    }
    return *this;
}
LinkList::~LinkList() {
    clear();
}

void LinkList::insert(const int& value) {
    LinkListNode* newNode = new LinkListNode(value);
    if (!m_head) {
        m_head = newNode;
    }
    else {
        LinkListNode* current = m_head;
        while (current->next()) {
            current = current->next();
        }
        current->setNext(newNode);
    }
    ++m_size;
}

void LinkList::remove(size_t index) {
    if (index >= m_size) throw std::out_of_range("Index out of range");//抛出异常
    LinkListNode* current = m_head;
    if (index == 0) {
        m_head = m_head->next();
        delete current;
    }
    else {
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next();
        }
        LinkListNode* temp = current->next();
        current->setNext(temp->next());
        delete temp;
    }
    --m_size;
}

void LinkList::update(size_t index, const int& value) {
    if (index >= m_size)throw std::out_of_range("Index out of range");//抛出异常
    LinkListNode* current = m_head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next();
    }
    current->setData(value); 
    
}

int LinkList::get(size_t index) const {
    if (index >= m_size)throw std::out_of_range("Index out of range");//抛出异常
    LinkListNode* current = m_head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next();
    }
    return current->getData();
}

size_t LinkList::getSize() const {
    return m_size;
}

void LinkList::print() const {
    LinkListNode* current = m_head;
    while (current) {
        std::cout << current->getData() << " -> ";
        current = current->next();
    }
    std::cout << "nullptr" << std::endl;
}

void LinkList::clear() {
    while (m_head) {
        LinkListNode* temp = m_head;
        m_head = m_head->next();
        delete temp;
    }
    m_size = 0;
}
