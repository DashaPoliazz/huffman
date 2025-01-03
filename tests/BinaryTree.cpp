#include "../include/BinaryTree.h"
#include <gtest/gtest.h>
#include <iostream>

// Test for creating a node
TEST(NodeTest, TestForCreatingNode) {
    Node<int> node(42);
    EXPECT_EQ(node.value, 42);
}

// Test for setting value
TEST(NodeTest, TestSetValue) {
    Node<int> node(42);
    node.set_value(100);
    EXPECT_EQ(node.value, 100);
}

// Test for setting left child
TEST(NodeTest, TestSetLeft) {
    Node<int> node(10);
    node.set_left(5);
    ASSERT_NE(node.get_left(), nullptr);   // Left child should not be null
    EXPECT_EQ(node.get_left()->value, 5);
}

// Test for setting right child
TEST(NodeTest, TestSetRight) {
    Node<int> node(10);
    node.set_right(15);
    ASSERT_NE(node.get_right(), nullptr);   // Right child should not be null
    EXPECT_EQ(node.get_right()->value, 15);
}

// Test for setting both left and right children
TEST(NodeTest, TestSetLeftAndRight) {
    Node<int> node(10);
    node.set_left(5);
    node.set_right(15);

    ASSERT_NE(node.get_left(), nullptr);    // Left child should not be null
    ASSERT_NE(node.get_right(), nullptr);   // Right child should not be null

    EXPECT_EQ(node.get_left()->value, 5);
    EXPECT_EQ(node.get_right()->value, 15);
}

// Test for overwriting left child
TEST(NodeTest, TestOverwriteLeft) {
    Node<int> node(10);
    node.set_left(5);
    node.set_left(20);   // Overwrite the left child

    ASSERT_NE(node.get_left(), nullptr);
    EXPECT_EQ(node.get_left()->value, 20);
}

// Test for overwriting right child
TEST(NodeTest, TestOverwriteRight) {
    Node<int> node(10);
    node.set_right(15);
    node.set_right(30);   // Overwrite the right child

    ASSERT_NE(node.get_right(), nullptr);
    EXPECT_EQ(node.get_right()->value, 30);
}

// Test for lvalue reference as child
TEST(NodeTest, TestSetLeftWithLValue) {
    Node<int> node(10);
    int left_value = 5;
    node.set_left(left_value);   // Passing lvalue reference

    ASSERT_NE(node.get_left(), nullptr);
    EXPECT_EQ(node.get_left()->value, 5);
}

// Test for rvalue reference as child
TEST(NodeTest, TestSetRightWithRValue) {
    Node<int> node(10);
    node.set_right(15);   // Passing rvalue

    ASSERT_NE(node.get_right(), nullptr);
    EXPECT_EQ(node.get_right()->value, 15);
}
