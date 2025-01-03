#ifndef TREEBUILDER_H
#define TREEBUILDER_H

#include "queue"
#include "string"
#include <queue>
#include <unordered_map>

struct CharQueueElement {
    char ch;
    long long frequency;

    CharQueueElement(char ch, long long frequency)
        : ch(ch)
        , frequency(frequency) {
    }
    bool operator>(const CharQueueElement& other) const {
        return frequency > other.frequency;
    }
};

using FrequencyTable = std::unordered_map<char, long long>;
using CharQueue =
    std::priority_queue<CharQueueElement, std::vector<CharQueueElement>, std::greater<>>;

class TreeBuilder {
public:
    std::string& text;

    explicit TreeBuilder(std::string& text)
        : text(text) {
    }

    /* getters for testing purposes */
    const FrequencyTable get_frequency_table() const {
        return build_frequency_table();
    }
    const CharQueue get_char_queue() const {
        return build_char_queue();
    }

private:
    const CharQueue build_char_queue() const {
        FrequencyTable frequency_table = build_frequency_table();
        CharQueue char_queue;
        for (const auto& [ch, freq] : frequency_table) {
            CharQueueElement char_queue_element(ch, freq);
            char_queue.push(char_queue_element);
        }
        return char_queue;
    }

    const FrequencyTable build_frequency_table() const {
        FrequencyTable frequency_table;
        for (char ch : text) {
            if (frequency_table.count(ch)) {
                frequency_table[ch]++;
            } else {
                frequency_table[ch] = 1;
            }
        }
        return frequency_table;
    }
};

#endif
