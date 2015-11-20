#include "../rbbst.h"
#include "gtest/gtest.h"


TEST(RBTreeTest, ZigZig) {
    RedBlackTree<int,int> b;

    b.add(std::make_pair(25, 0));
    b.add(std::make_pair(20, 0));
    b.add(std::make_pair(30, 0));
    b.add(std::make_pair(10, 0));
    
    

    RedBlackTree<int,int>::iterator it = b.begin();

    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(b.getColor(10), red);

    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(b.getColor(20), black);

    ++it;
    EXPECT_EQ(it->first, 25);
    EXPECT_EQ(b.getColor(25), black);

    ++it;
    EXPECT_EQ(it->first, 30);
    EXPECT_EQ(b.getColor(30), black);

    ++it;
    EXPECT_EQ(it, b.end());
}

TEST(RBTreeTest, ZigZag) {
    RedBlackTree<int,int> b;

    b.add(std::make_pair(25, 0));
    b.add(std::make_pair(10, 0));
    b.add(std::make_pair(30, 0));
    b.add(std::make_pair(20, 0));
    
    

    RedBlackTree<int,int>::iterator it = b.begin();

    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(b.getColor(10), black);

    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(b.getColor(20), red);

    ++it;
    EXPECT_EQ(it->first, 25);
    EXPECT_EQ(b.getColor(25), black);

    ++it;
    EXPECT_EQ(it->first, 30);
    EXPECT_EQ(b.getColor(30), black);

    ++it;
    EXPECT_EQ(it, b.end());
}


TEST(RBTreeTest, RightRight) {
    RedBlackTree<int,int> b;

    b.add(std::make_pair(10, 0));
    b.add(std::make_pair(20, 0));
    b.add(std::make_pair(30, 0));
    

    RedBlackTree<int,int>::iterator it = b.begin();

    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(b.getColor(10), red);

    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(b.getColor(20), black);

    ++it;
    EXPECT_EQ(it->first, 30);
    EXPECT_EQ(b.getColor(30), red);

    ++it;
    EXPECT_EQ(it, b.end());
}

TEST(RBTreeTest, LeftLeft) {
    RedBlackTree<int,int> b;

    b.add(std::make_pair(30, 0));
    b.add(std::make_pair(20, 0));
    b.add(std::make_pair(10, 0));
    

    RedBlackTree<int,int>::iterator it = b.begin();

    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(b.getColor(10), red);

    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(b.getColor(20), black);

    ++it;
    EXPECT_EQ(it->first, 30);
    EXPECT_EQ(b.getColor(30), red);

    ++it;
    EXPECT_EQ(it, b.end());
}

TEST(RBTreeTest, LeftRight) {
    RedBlackTree<int,int> b;

    b.add(std::make_pair(30, 0));
    b.add(std::make_pair(10, 0));
    b.add(std::make_pair(20, 0));
    

    RedBlackTree<int,int>::iterator it = b.begin();

    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(b.getColor(10), red);

    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(b.getColor(20), black);

    ++it;
    EXPECT_EQ(it->first, 30);
    EXPECT_EQ(b.getColor(30), red);

    ++it;
    EXPECT_EQ(it, b.end());
}

TEST(RBTreeTest, RightLeft) {
    RedBlackTree<int,int> b;

    b.add(std::make_pair(10, 0));
    b.add(std::make_pair(30, 0));
    b.add(std::make_pair(20, 0));
    

    RedBlackTree<int,int>::iterator it = b.begin();

    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(b.getColor(10), red);

    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(b.getColor(20), black);

    ++it;
    EXPECT_EQ(it->first, 30);
    EXPECT_EQ(b.getColor(30), red);

    ++it;
    EXPECT_EQ(it, b.end());
}

TEST(RBTreeTest, BasicTest) {
    RedBlackTree<int,int> b;

    b.add(std::make_pair(10, 0));
    b.add(std::make_pair(20, 0));
    b.add(std::make_pair(30, 0));
    b.add(std::make_pair(15, 0));
    b.add(std::make_pair(25, 0));
    b.add(std::make_pair(25, 0));
    b.add(std::make_pair(30, 0));
    

    RedBlackTree<int,int>::iterator it = b.begin();

    it;
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(b.getColor(10), black);

    ++it;
    EXPECT_EQ(it->first, 15);
    EXPECT_EQ(b.getColor(15), red);

    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(b.getColor(20), black);

    ++it;
    EXPECT_EQ(it->first, 25);
    EXPECT_EQ(b.getColor(25), red);

    ++it;
    EXPECT_EQ(it->first, 30);
    EXPECT_EQ(b.getColor(30), black);

    ++it;
    EXPECT_EQ(it, b.end());
}

TEST(RBTreeTest, AnyOrderTest) {
    RedBlackTree<int,int> b;

    b.add(std::make_pair(10, 0));
    b.add(std::make_pair(20, 0));
    b.add(std::make_pair(30, 0));
    b.add(std::make_pair(15, 0));
    b.add(std::make_pair(25, 0));
    b.add(std::make_pair(12, 0));
    b.add(std::make_pair(5, 0));
    b.add(std::make_pair(3, 0));
    b.add(std::make_pair(8, 0));
    b.add(std::make_pair(27, 0));
    b.add(std::make_pair(40, 0));
    b.add(std::make_pair(50, 0));
    b.add(std::make_pair(45, 0));
    

    RedBlackTree<int,int>::iterator it = b.begin();

    
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(b.getColor(3), black);

    ++it;
    EXPECT_EQ(it->first, 5);
    EXPECT_EQ(b.getColor(5), black);

    ++it;
    EXPECT_EQ(it->first, 8);
    EXPECT_EQ(b.getColor(8), red);

    ++it;
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(b.getColor(10), black);

    ++it;
    EXPECT_EQ(it->first, 12);
    EXPECT_EQ(b.getColor(12), black);

    ++it;
    EXPECT_EQ(it->first, 15);
    EXPECT_EQ(b.getColor(15), black);

    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(b.getColor(20), red);

    ++it;
    EXPECT_EQ(it->first, 25);
    EXPECT_EQ(b.getColor(25), black);

    ++it;
    EXPECT_EQ(it->first, 27);
    EXPECT_EQ(b.getColor(27), black);

    ++it;
    EXPECT_EQ(it->first, 30);
    EXPECT_EQ(b.getColor(30), black);

    ++it;
    EXPECT_EQ(it->first, 40);
    EXPECT_EQ(b.getColor(40), red);

    ++it;
    EXPECT_EQ(it->first, 45);
    EXPECT_EQ(b.getColor(45), red);

    ++it;
    EXPECT_EQ(it->first, 50);
    EXPECT_EQ(b.getColor(50), black);

    ++it;
    EXPECT_EQ(it, b.end());
}
