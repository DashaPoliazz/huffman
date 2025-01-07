#include "../../../include/Huffman.h"
#include <gtest/gtest.h>

// Test with a basic frequency distribution and internal nodes present
TEST(BuildHuffmanTree, BasicEncodingWithInternalNodes) {
    Huffman huffman("aaabbc");
    auto encoding_table = huffman.get_encoding_table();

    // Internal nodes are allowed, but encoding lengths should still reflect frequency
    ASSERT_EQ(encoding_table["a"].length(), 1);
    ASSERT_EQ(encoding_table["b"].length(), 2);
    ASSERT_EQ(encoding_table["c"].length(), 2);

    // Ensure internal nodes exist in the tree (root should not have a symbol)
    ASSERT_EQ(huffman.huffman_tree->value.str, "abc");   // Root contains all characters combined
}

// Test with a single character (internal nodes won't be created here)
TEST(BuildHuffmanTree, SingleCharacterInput) {
    Huffman huffman("aaaa");
    auto encoding_table = huffman.get_encoding_table();

    // Only one unique character, no internal nodes should exist
    ASSERT_EQ(encoding_table.size(), 1);
    ASSERT_EQ(encoding_table["a"].length(), 1);
}

// Test with all unique characters and internal nodes
TEST(BuildHuffmanTree, AllUniqueCharacters) {
    Huffman huffman("abcdef");
    auto encoding_table = huffman.get_encoding_table();

    // Since all characters are unique, tree depth should be balanced
    for (char ch : std::string("abcdef")) {
        ASSERT_TRUE(encoding_table.find(std::string(1, ch)) != encoding_table.end());
    }

    // Verify internal nodes contain merged symbols
    ASSERT_EQ(huffman.huffman_tree->value.str, "abcdef");
}

// Test with an empty string (no nodes created)
TEST(BuildHuffmanTree, EmptyInputWithInternalNodes) {
    Huffman huffman("");
    auto encoding_table = huffman.get_encoding_table();

    // Expecting no encodings for an empty input
    ASSERT_TRUE(encoding_table.empty());
    ASSERT_EQ(huffman.huffman_tree, nullptr);
}

// Test with repeated characters only (no internal nodes created)
TEST(BuildHuffmanTree, RepeatedCharactersOnly) {
    Huffman huffman("bbbbbbbb");
    auto encoding_table = huffman.get_encoding_table();

    // Since there's only one character, it should have a single leaf
    ASSERT_EQ(encoding_table.size(), 1);
    ASSERT_EQ(encoding_table["b"].length(), 1);
}

// Test with special characters (internal nodes expected)
TEST(BuildHuffmanTree, SpecialCharactersWithInternalNodes) {
    Huffman huffman("a b c a");
    auto encoding_table = huffman.get_encoding_table();

    // Expect 4 unique characters (space included)
    ASSERT_EQ(encoding_table.size(), 4);
    ASSERT_TRUE(encoding_table.find(" ") != encoding_table.end());

    // Verify internal nodes exist
    ASSERT_EQ(huffman.huffman_tree->value.str, " abc");
}

// Test for case sensitivity (internal nodes should merge all characters)
TEST(BuildHuffmanTree, CaseSensitivityWithInternalNodes) {
    Huffman huffman("aAbBcC");
    auto encoding_table = huffman.get_encoding_table();

    // Verify case sensitivity by ensuring both cases exist
    ASSERT_EQ(encoding_table.size(), 6);
    ASSERT_TRUE(encoding_table.find("a") != encoding_table.end());
    ASSERT_TRUE(encoding_table.find("A") != encoding_table.end());

    // Verify internal nodes hold all characters
    ASSERT_EQ(huffman.huffman_tree->value.str, "ABCabc");
}

// Test with a long input string where internal nodes are expected
TEST(BuildHuffmanTree, LongInputWithInternalNodes) {
    std::string long_text(1000, 'a');
    Huffman huffman(long_text);
    auto encoding_table = huffman.get_encoding_table();

    // Only one unique character, so no internal nodes expected
    ASSERT_EQ(encoding_table.size(), 1);
    ASSERT_EQ(encoding_table["a"].length(), 1);
}

// Test for encoding consistency with the same input
TEST(BuildHuffmanTree, ConsistencyTestWithInternalNodes) {
    Huffman huffman1("aaabbc");
    auto encoding_table1 = huffman1.get_encoding_table();

    Huffman huffman2("aaabbc");
    auto encoding_table2 = huffman2.get_encoding_table();

    // Encodings should be consistent between identical inputs
    ASSERT_EQ(encoding_table1, encoding_table2);
    ASSERT_EQ(huffman1.huffman_tree->value.str, huffman2.huffman_tree->value.str);
}

// Test for correct ordering by frequency (with internal nodes)
TEST(BuildHuffmanTree, FrequencyOrderingTestWithInternalNodes) {
    Huffman huffman("aaabbc");
    auto frequency_table = huffman.get_frequency_table();

    // Frequencies should be calculated correctly
    ASSERT_EQ(frequency_table['a'], 3);
    ASSERT_EQ(frequency_table['b'], 2);
    ASSERT_EQ(frequency_table['c'], 1);

    // Ensure root internal node contains all characters combined
    ASSERT_EQ(huffman.huffman_tree->value.str, "abc");
}
