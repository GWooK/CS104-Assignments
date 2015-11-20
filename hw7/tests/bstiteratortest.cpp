#include "../bst.h"
#include "gtest/gtest.h"

TEST(BstIteratorTest, BasicTest) {
    BinarySearchTree<int,int> b;
    b.add(std::make_pair(1, 0));
    b.add(std::make_pair(2, 0));
    b.add(std::make_pair(3, 0));

    BinarySearchTree<int,int>::iterator it = b.begin();
    EXPECT_EQ(it->first, 1);

    ++it;
    EXPECT_EQ(it->first, 2);

    ++it;
    EXPECT_EQ(it->first, 3);

    ++it;
    EXPECT_EQ(it, b.end());
}

TEST(BstIteratorTest, BasicAnyOrderTest) {
    BinarySearchTree<int,int> b;
    b.add(std::make_pair(3, 0));
    b.add(std::make_pair(2, 0));
    b.add(std::make_pair(1, 0));
    b.add(std::make_pair(5, 0));
    b.add(std::make_pair(7, 0));
    b.add(std::make_pair(7, 1));
    b.add(std::make_pair(4, 0));

    BinarySearchTree<int,int>::iterator it = b.begin();
    EXPECT_EQ(it->first, 1);

    ++it;
    EXPECT_EQ(it->first, 2);

    ++it;
    EXPECT_EQ(it->first, 3);

    ++it;
    EXPECT_EQ(it->first, 4);

    ++it;
    EXPECT_EQ(it->first, 5);

    ++it;
    EXPECT_EQ(it->first, 7);
    EXPECT_EQ(it->second, 1);

    ++it;
    EXPECT_EQ(it, b.end());
}
