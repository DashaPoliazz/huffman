#include "../../../include/Huffman.h"
#include <gtest/gtest.h>
#include <string>

// Test encoding with an empty string
TEST(EmptyStringEncoding, EncodeString) {
    std::string text = "";
    Huffman huffman(text);
    std::string encoded = huffman.encode(text);
    EXPECT_TRUE(encoded.empty());
}

// Test encoding a string with repeated characters
TEST(SimpleStringEncoding, EncodeSimpleString) {
    std::string text = "aaaa";
    Huffman huffman(text);
    std::string encoded = huffman.encode(text);
    std::string expected =
        huffman.get_encoding_table().at("a") + huffman.get_encoding_table().at("a") +
        huffman.get_encoding_table().at("a") + huffman.get_encoding_table().at("a");
    EXPECT_EQ(encoded, expected);
}

// Test encoding a string where all characters are unique
TEST(UniqueCharactersEncoding, EncodeUniqueChars) {
    std::string text = "abcd";
    Huffman huffman(text);
    std::string encoded = huffman.encode(text);
    EXPECT_FALSE(encoded.empty());
}

// Test encoding followed by decoding for correctness
TEST(EncodingDecodingConsistency, EncodeDecodeConsistency) {
    std::string text = "hello, world!";
    Huffman huffman(text);
    std::string encoded = huffman.encode(text);
    std::string decoded = huffman.decode(encoded);
    EXPECT_EQ(text, decoded);
}

// Test encoding a single-character string
TEST(SingleCharacterString, EncodeSingleCharacter) {
    std::string text = "a";
    Huffman huffman(text);
    std::string encoded = huffman.encode(text);
    EXPECT_EQ(encoded.length(), huffman.get_encoding_table().at("a").length());
}

// Test decoding an empty string
TEST(EmptyStringDecoding, DecodeEmptyString) {
    std::string text = "";
    Huffman huffman(text);
    std::string decoded = huffman.decode(text);
    EXPECT_TRUE(decoded.empty());
}

// Test the symmetry of encoding and decoding (input equals output)
TEST(SymmetricEncodingDecoding, EncodeAndDecodeSame) {
    std::string text = "testing symmetry";
    Huffman huffman(text);
    std::string encoded = huffman.encode(text);
    std::string decoded = huffman.decode(encoded);
    EXPECT_EQ(decoded, text);
}

// Test encoding and decoding a string with all unique characters
TEST(AllUniqueCharacters, EncodeDecodeUnique) {
    std::string text = "abcdefghijklmnopqrstuvwxyz";
    Huffman huffman(text);
    std::string encoded = huffman.encode(text);
    std::string decoded = huffman.decode(encoded);
    EXPECT_EQ(decoded, text);
}
