#include "../../../include/Huffman.h"
#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

// Test for basic frequency table creation
TEST(FrequencyTableTest, BasicFrequencyTest) {
    Huffman huffman("hello");
    auto frequency_table = huffman.get_frequency_table();

    // Check if frequencies are correctly counted
    EXPECT_EQ(frequency_table['h'], 1);
    EXPECT_EQ(frequency_table['e'], 1);
    EXPECT_EQ(frequency_table['l'], 2);
    EXPECT_EQ(frequency_table['o'], 1);
}

// Test for an empty string input
TEST(FrequencyTableTest, EmptyStringTest) {
    Huffman huffman("");
    auto frequency_table = huffman.get_frequency_table();

    // An empty string should result in an empty frequency table
    EXPECT_TRUE(frequency_table.empty());
}

// Test for a string with repeating characters
TEST(FrequencyTableTest, RepeatingCharactersTest) {
    Huffman huffman("aaa");
    auto frequency_table = huffman.get_frequency_table();

    // Only one unique character with a frequency of 3
    EXPECT_EQ(frequency_table['a'], 3);
    EXPECT_EQ(frequency_table.size(), 1);
}

// Test for a string containing spaces and special characters
TEST(FrequencyTableTest, SpecialCharactersTest) {
    Huffman huffman("a b c a");
    auto frequency_table = huffman.get_frequency_table();

    // Spaces and characters should be counted correctly
    EXPECT_EQ(frequency_table['a'], 2);
    EXPECT_EQ(frequency_table['b'], 1);
    EXPECT_EQ(frequency_table['c'], 1);
    EXPECT_EQ(frequency_table[' '], 3);
}

// Test for a string with all unique characters
TEST(FrequencyTableTest, UniqueCharactersTest) {
    Huffman huffman("abc123");
    auto frequency_table = huffman.get_frequency_table();

    // Each character should have a count of 1
    EXPECT_EQ(frequency_table['a'], 1);
    EXPECT_EQ(frequency_table['b'], 1);
    EXPECT_EQ(frequency_table['c'], 1);
    EXPECT_EQ(frequency_table['1'], 1);
    EXPECT_EQ(frequency_table['2'], 1);
    EXPECT_EQ(frequency_table['3'], 1);
    EXPECT_EQ(frequency_table.size(), 6);   // All characters are unique
}
