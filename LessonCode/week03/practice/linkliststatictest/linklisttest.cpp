#include "linklisttest.h"



void linklist_unit_test::LinkListTest::SetUp()
{
    m_linkListFirst.insert(10);
    m_linkListFirst.insert(20);
    m_linkListFirst.insert(30);

    m_linkListSecond.insert(40);
    m_linkListSecond.insert(50);
    m_linkListSecond.insert(60);

    m_linkListThird.insert(70);
    m_linkListThird.insert(80);
    m_linkListThird.insert(90);
    std::cout << "SetUp()" << std::endl;
}

void linklist_unit_test::LinkListTest::TearDown()
{
}