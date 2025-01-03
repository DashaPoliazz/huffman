#include "../include/TreeBuilder.h"
#include <gtest/gtest.h>
#include <stdio.h>

// Test for build_frequency_table
TEST(TreeBuilderTest, BuildFrequencyTable) {
    std::string text = "hello";
    TreeBuilder builder(text);

    std::cout << "FROM BUILD FREQUENCY" << "\n";
    FrequencyTable frequency_table = builder.get_frequency_table();

    EXPECT_EQ(frequency_table['h'], 1);
    EXPECT_EQ(frequency_table['e'], 1);
    EXPECT_EQ(frequency_table['l'], 2);
    EXPECT_EQ(frequency_table['o'], 1);
    EXPECT_EQ(frequency_table.size(), 4);   // Total unique characters
}

// Test for build_char_queue
TEST(TreeBuilderTest, BuildCharQueue) {
    std::string text = "hello";
    TreeBuilder builder(text);

    CharQueue char_queue = builder.get_char_queue();

    // Check the elements of the priority queue
    ASSERT_FALSE(char_queue.empty());

    CharQueueElement top = char_queue.top();
    EXPECT_EQ(top.frequency, 1);
    char_queue.pop();

    top = char_queue.top();
    EXPECT_EQ(top.frequency, 1);
    char_queue.pop();

    top = char_queue.top();
    EXPECT_EQ(top.frequency, 1);
    char_queue.pop();

    top = char_queue.top();
    EXPECT_EQ(top.frequency, 2);
    char_queue.pop();

    EXPECT_TRUE(char_queue.empty());
}
