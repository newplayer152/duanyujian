#include "gtest/gtest.h"
#include "linklisttest.h"

namespace linklist_unit_test
{
    // 默认构造函数测试
    TEST_F(LinkListTest, DefaultConstructor) {
        LinkList emptyList;
        EXPECT_EQ(0, emptyList.getSize()); // 检查默认构造是否为空
        EXPECT_EQ(3, m_linkListFirst.getSize()); // 检查已有链表的大小
    }

    // 测试插入和获取元素
    TEST_F(LinkListTest, InsertAndGet) {
        EXPECT_EQ(10, m_linkListFirst.get(0));
        EXPECT_EQ(20, m_linkListFirst.get(1));
        EXPECT_EQ(30, m_linkListFirst.get(2));

        EXPECT_EQ(40, m_linkListSecond.get(0));
        EXPECT_EQ(50, m_linkListSecond.get(1));
        EXPECT_EQ(60, m_linkListSecond.get(2));

        EXPECT_EQ(70, m_linkListThird.get(0));
        EXPECT_EQ(80, m_linkListThird.get(1));
        EXPECT_EQ(90, m_linkListThird.get(2));
    }

    // 测试删除元素
    TEST_F(LinkListTest, Remove) {
        m_linkListFirst.remove(0);
        EXPECT_EQ(2, m_linkListFirst.getSize());
        EXPECT_EQ(20, m_linkListFirst.get(0));

        m_linkListSecond.remove(1);
        EXPECT_EQ(2, m_linkListSecond.getSize());
        EXPECT_EQ(60, m_linkListSecond.get(1));

        m_linkListThird.remove(2);
        EXPECT_EQ(2, m_linkListThird.getSize());
    }

    // 测试更新元素
    TEST_F(LinkListTest, Update) {
        m_linkListFirst.update(0, 100);
        EXPECT_EQ(100, m_linkListFirst.get(0));

        m_linkListSecond.update(2, 200);
        EXPECT_EQ(200, m_linkListSecond.get(2));

        m_linkListThird.update(1, 300);
        EXPECT_EQ(300, m_linkListThird.get(1));
    }

    // 测试清空链表
    TEST_F(LinkListTest, Clear) {
        m_linkListFirst.clear();
        EXPECT_EQ(0, m_linkListFirst.getSize());

        m_linkListSecond.clear();
        EXPECT_EQ(0, m_linkListSecond.getSize());

        m_linkListThird.clear();
        EXPECT_EQ(0, m_linkListThird.getSize());
    }

    // 测试链表的拷贝构造
    TEST_F(LinkListTest, CopyConstructor) {

        LinkList copyList(m_linkListFirst);
        EXPECT_EQ(copyList.getSize(), m_linkListFirst.getSize());
        EXPECT_EQ(copyList.get(0), m_linkListFirst.get(0));
        EXPECT_EQ(copyList.get(1), m_linkListFirst.get(1));
        EXPECT_EQ(copyList.get(2), m_linkListFirst.get(2));
    }

    // 测试链表的拷贝赋值运算符
    TEST_F(LinkListTest, CopyAssignment) {
        LinkList copyList ;
        copyList = static_cast<const LinkList&>(m_linkListSecond);
        EXPECT_EQ(copyList.getSize(), m_linkListSecond.getSize());
        EXPECT_EQ(copyList.get(0), m_linkListSecond.get(0));
        EXPECT_EQ(copyList.get(1), m_linkListSecond.get(1));
        EXPECT_EQ(copyList.get(2), m_linkListSecond.get(2));
 
    }

    // 测试链表的移动构造
    TEST_F(LinkListTest, MoveConstructor) {
        LinkList movedList(std::move(m_linkListThird));
        EXPECT_EQ(3, movedList.getSize());
        EXPECT_EQ(70, movedList.get(0));
        EXPECT_EQ(80, movedList.get(1));
        EXPECT_EQ(90, movedList.get(2));
        EXPECT_EQ(0, m_linkListThird.getSize()); // 被移动后，原链表应为空
    }

    // 测试链表的移动赋值运算符
    TEST_F(LinkListTest, MoveAssignment) {
        LinkList movedList;
        movedList = std::move(m_linkListFirst);
        EXPECT_EQ(3, movedList.getSize());
        EXPECT_EQ(10, movedList.get(0));
        EXPECT_EQ(20, movedList.get(1));
        EXPECT_EQ(30, movedList.get(2));
        EXPECT_EQ(0, m_linkListFirst.getSize()); // 被移动后，原链表应为空
    }

    // 测试打印方法
    TEST_F(LinkListTest, Print) {
        m_linkListFirst.print();
    }
}  // namespace linklist_unit_test