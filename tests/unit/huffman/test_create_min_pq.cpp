#include "../../../include/Huffman.h"
#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

// Test for basic priority queue functionality
TEST(PriorityQueueTest, BasicFunctionality) {
    Huffman huffman("aabbc");
    auto pq = huffman.get_node_min_pq();

    // Check the size of the priority queue (3 unique characters: a, b, c)
    EXPECT_EQ(pq.size(), 3);

    // Verify the node with the lowest frequency is at the top ('c' with frequency 1)
    const auto& top_node = pq.top();
    EXPECT_EQ(top_node->value.str, "c");
    EXPECT_EQ(top_node->value.freq, 1);
}

// Test for an empty input
TEST(PriorityQueueTest, EmptyInputTest) {
    Huffman huffman("");
    auto pq = huffman.get_node_min_pq();

    // The queue should be empty for an empty input
    EXPECT_EQ(pq.size(), 0);
}

// Test for a single character input
TEST(PriorityQueueTest, SingleCharacterInput) {
    Huffman huffman("aaaa");
    auto pq = huffman.get_node_min_pq();

    // Should contain only one unique node
    EXPECT_EQ(pq.size(), 1);

    const auto& top_node = pq.top();
    EXPECT_EQ(top_node->value.str, "a");
    EXPECT_EQ(top_node->value.freq, 4);
}

// Test for multiple characters with the same frequency
TEST(PriorityQueueTest, EqualFrequencyTest) {
    Huffman huffman("abc");
    auto pq = huffman.get_node_min_pq();

    // All characters should have frequency 1
    EXPECT_EQ(pq.size(), 3);

    while (!pq.empty()) {
        const auto& top_node = pq.top();
        EXPECT_EQ(top_node->value.freq, 1);
        pq.pop();
    }
}

// Test for correct ordering with different frequencies
TEST(PriorityQueueTest, OrderingTest) {
    Huffman huffman("aaaabbc");
    auto pq = huffman.get_node_min_pq();

    // The lowest frequency should be on top ('c' with frequency 1)
    const auto& top_node = pq.top();
    EXPECT_EQ(top_node->value.str, "c");
    EXPECT_EQ(top_node->value.freq, 1);
}

// Test for popping elements from the priority queue
TEST(PriorityQueueTest, PopElementsTest) {
    Huffman huffman("aaabbc");
    auto pq = huffman.get_node_min_pq();

    // The first element should be 'c' with frequency 1
    const auto& first_node = pq.top();
    EXPECT_EQ(first_node->value.str, "c");
    EXPECT_EQ(first_node->value.freq, 1);
    pq.pop();

    // The second element should be 'b' with frequency 2
    const auto& second_node = pq.top();
    EXPECT_EQ(second_node->value.str, "b");
    EXPECT_EQ(second_node->value.freq, 2);
    pq.pop();

    // The third element should be 'a' with frequency 3
    const auto& third_node = pq.top();
    EXPECT_EQ(third_node->value.str, "a");
    EXPECT_EQ(third_node->value.freq, 3);
    pq.pop();

    // The queue should be empty now
    EXPECT_TRUE(pq.empty());
}

// Test for inserting elements directly into the priority queue
TEST(PriorityQueueTest, DirectInsertionTest) {
    NodeMinPQ pq(node_comparator);

    pq.push(std::make_unique<Node<NodeValue>>(NodeValue{ "a", 5 }));
    pq.push(std::make_unique<Node<NodeValue>>(NodeValue{ "b", 2 }));
    pq.push(std::make_unique<Node<NodeValue>>(NodeValue{ "c", 3 }));

    // Expect the element with the lowest frequency on top ('b')
    const auto& top_node = pq.top();
    EXPECT_EQ(top_node->value.str, "b");
    EXPECT_EQ(top_node->value.freq, 2);
}

// Test for inserting a large number of elements
TEST(PriorityQueueTest, LargeInputTest) {
    Huffman huffman("aaaaaaaaaabbbbccccdd");
    auto pq = huffman.get_node_min_pq();

    // Four unique elements: a, b, c, d
    EXPECT_EQ(pq.size(), 4);

    // Verify the smallest frequency node ('d' with frequency 2)
    const auto& top_node = pq.top();
    EXPECT_EQ(top_node->value.str, "d");
    EXPECT_EQ(top_node->value.freq, 2);
}

// Test for priority queue with special characters
TEST(PriorityQueueTest, SpecialCharactersTest) {
    Huffman huffman("a b c a");
    auto pq = huffman.get_node_min_pq();

    // Four unique nodes including space character
    EXPECT_EQ(pq.size(), 4);

    // The top node should have the smallest frequency
    const auto& top_node = pq.top();
    EXPECT_EQ(top_node->value.freq, 1);
}
