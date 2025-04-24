#ifndef __LINKLLIST_LINKLISTNODE_H
#define __LINKLLIST_LINKLISTNODE_H

#include <iostream>
#include <string> 

class LinkListNode
{
public:
	explicit LinkListNode(const int &data);

	LinkListNode& operator=(const LinkListNode)=delete;
	LinkListNode(const LinkListNode& data)=delete;
	~LinkListNode() = default;

	int getData() const;
	LinkListNode* next();
	void setNext(LinkListNode* temp);
	void setData(int data);

private:
	int m_data;
	LinkListNode* m_next;

};


#endif // !__LINKLLIST_LINKLISTNODE_H



