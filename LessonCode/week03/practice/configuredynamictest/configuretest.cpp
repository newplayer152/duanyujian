#include <iostream>
#include "gtest/gtest.h"
#include "configure.h"

TEST(ConfigureTest, AddItem) {
    ExportConfigure* configure = getClassObj();
    
    EXPECT_EQ(configure->addItem("Alice"), 0);
    EXPECT_EQ(configure->addItem("Alice"), 0);
    EXPECT_EQ(configure->addItem("Alice2"), 1);
    releaseClassObj(configure);
}

TEST(ConfigureTest, GetItem) {
    ExportConfigure* configure = getClassObj();
    EXPECT_EQ(configure->addItem("Alice"), 0);
    EXPECT_EQ(configure->addItem("Alice2"), 1);
    EXPECT_EQ(configure->getItem(-1), "");
    EXPECT_EQ(configure->getItem(0), "Alice");
    EXPECT_EQ(configure->getItem(1), "Alice2");
    EXPECT_EQ(configure->getItem(2), "");
    releaseClassObj(configure);
}

TEST(ConfigureTest, GetSize) {
    ExportConfigure* configure = getClassObj();
    EXPECT_EQ(configure->addItem("Alice"), 0);
    EXPECT_EQ(configure->addItem("Alice2"), 1);
    EXPECT_EQ(configure->getSize(), 2);
    releaseClassObj(configure);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
