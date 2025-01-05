#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "./BinaryTree.h"
#include "./Decoder.h"
#include "unordered_map"
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

class Huffman : public Decoder {
    /* Outer handles */
public:
    explicit Huffman(std::string text)
        : Decoder(std::move(text)) {
    }

    std::string encode(std::string& text) const override {
        return text;
    }
    std::string decode(std::string& text) const override {
        return text;
    }

    /* getters for testing purposes */
    FrequencyTable get_frequency_table() const {
        return create_frequency_table();
    }
    NodeMinPQ get_node_min_pq() const {
        return create_node_min_pq();
    }

    /* Inner machinery */
private:
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
