#ifndef __LINKLIST_KQUEUETEST_H
#define __LINKLIST_KQUEUETEST_H
#include <iostream>
#include "gtest/gtest.h"
#include "linklist.h"
namespace linklist_unit_test {
	class LinkListTest:public testing::Test
	{
	protected:
		void SetUp() override;
		void TearDown() override;

		LinkList  m_linkListFirst;
		LinkList  m_linkListSecond;
		LinkList  m_linkListThird;
	};

}

#endif //__LINKLIST_KQUEUETEST_H