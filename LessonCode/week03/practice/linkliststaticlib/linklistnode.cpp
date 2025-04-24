
#include "linklistnode.h"


LinkListNode::LinkListNode(const int& data):m_data(data), m_next(nullptr)
{
}

int LinkListNode::getData() const
{
	return m_data;
}

LinkListNode* LinkListNode::next()
{
	return m_next;
}

void LinkListNode::setNext(LinkListNode* temp)
{
	m_next = temp;
}

void LinkListNode::setData(int data) {
	m_data = data;
}

