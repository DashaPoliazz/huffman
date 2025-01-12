#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "./BinaryTree.h"
#include "./Decoder.h"
#include "unordered_map"
#include <algorithm>
#include <iostream>
#include <queue>

/* looks a little bit awful in this file and in general */
struct NodeValue {
    std::string str;
    long long freq;
};
using NodePtr = std::unique_ptr<Node<NodeValue>>;

inline auto node_comparator = [](const NodePtr& a, const NodePtr& b) {
    return a->value.freq > b->value.freq;
};

using FrequencyTable = std::unordered_map<char, long long>;
using NodeMinPQ = std::priority_queue<NodePtr, std::vector<NodePtr>, decltype(node_comparator)>;
using EncodingTable = std::unordered_map<std::string, std::string>;

class Huffman : public Decoder {
    /* Outer handles */
public:
    NodePtr huffman_tree;

    explicit Huffman(std::string text)
        : Decoder(std::move(text)) {
        huffman_tree = build_huffman_tree();

        std::string code_buffer;
        build_encoding_table(huffman_tree.get(), code_buffer);
        for (const auto& [symbol, code] : direct_encoding_table) {
            reversed_encoding_table[code] = symbol;
        }
    }

    std::string encode(std::string& text) override {
        std::string decoded;
        for (char ch : text) {
            std::string str_to_decode = std::string(1, ch);
            decoded += direct_encoding_table[str_to_decode];
        }
        return decoded;
    }

    std::string decode(std::string& text) override {
        std::string decoded;
        std::string encoding;

        for (char bit : text) {
            encoding += bit;

            if (reversed_encoding_table.count(encoding)) {
                decoded += reversed_encoding_table[encoding];
                encoding.clear();
            }
        }

        return decoded;
    }

    /* getters for testing purposes */
    FrequencyTable get_frequency_table() const {
        return create_frequency_table();
    }
    NodeMinPQ get_node_min_pq() const {
        return create_node_min_pq();
    }
    EncodingTable get_encoding_table() const {
        return direct_encoding_table;
    }

    /* Inner machinery */
private:
    EncodingTable direct_encoding_table;
    EncodingTable reversed_encoding_table;

    void build_encoding_table(const Node<NodeValue>* node, std::string& code) {
        if (!node) {
            return;
        }

        bool is_leaf = !node->get_left() && !node->get_right();

        if (is_leaf) {
            auto element_to_encode = node->value.str;
            direct_encoding_table[element_to_encode] = code;
            return;
        }

        if (node->get_left()) {
            code.push_back('0');
            build_encoding_table(node->get_left(), code);
            code.pop_back();
        }
        if (node->get_right()) {
            code.push_back('1');
            build_encoding_table(node->get_right(), code);
            code.pop_back();
        }
    }

    NodePtr build_huffman_tree() const {
        NodeMinPQ min_pq = create_node_min_pq();

        if (min_pq.empty()) {
            return nullptr;
        }

        if (min_pq.size() == 1) {
            NodeValue dummy_value{ "dummy_root", 0 };
            NodePtr parent = std::make_unique<Node<NodeValue>>(std::move(dummy_value));
            NodePtr only_node = std::move(const_cast<NodePtr&>(min_pq.top()));
            min_pq.pop();

            parent->left = std::move(only_node);

            return parent;
        }

        while (min_pq.size() > 1) {
            NodePtr left = std::move(const_cast<NodePtr&>(min_pq.top()));
            min_pq.pop();
            NodePtr right = std::move(const_cast<NodePtr&>(min_pq.top()));
            min_pq.pop();

            /* tree will be determined with the order of nodes */
            std::sort(left->value.str.begin(), left->value.str.end());
            std::sort(right->value.str.begin(), right->value.str.end());

            std::string merged_str = left->value.str + right->value.str;
            std::sort(merged_str.begin(), merged_str.end());

            long long combined_freq = left->value.freq + right->value.freq;
            NodeValue merged_value{ merged_str, combined_freq };
            NodePtr parent = std::make_unique<Node<NodeValue>>(std::move(merged_value));

            /* smaller string will be in the left part */
            if (left->value.str < right->value.str) {
                parent->left = std::move(left);
                parent->right = std::move(right);
            } else {
                parent->left = std::move(right);
                parent->right = std::move(left);
            }

            min_pq.push(std::move(parent));
        }

        return std::move(const_cast<NodePtr&>(min_pq.top()));
    }

    NodeMinPQ create_node_min_pq() const {
        FrequencyTable frequency_table = create_frequency_table();
        NodeMinPQ node_min_pq(node_comparator);

        for (const auto& [ch, frequency] : frequency_table) {
            NodePtr node_ptr =
                std::make_unique<Node<NodeValue>>(NodeValue{ std::string(1, ch), frequency });
            node_min_pq.push(std::move(node_ptr));
        }

        return node_min_pq;
    }

    FrequencyTable create_frequency_table() const {
        std::unordered_map<char, long long> frequency_table;
        for (char ch : text_to_decode) {
            frequency_table[ch]++;
        }
        return frequency_table;
    }
};

#endif
