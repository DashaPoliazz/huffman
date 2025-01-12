#ifndef DECODER_H
#define DECODER_H

#include <string>

/* Absstract-base class */
class Decoder {

public:
    explicit Decoder(std::string text)
        : text_to_decode(std::move(text)) {
    }

    /* pure virtual functions */
    virtual std::string encode(std::string& text) = 0;
    virtual std::string decode(std::string& text) = 0;

    virtual ~Decoder() = default;

protected:
    std::string text_to_decode;
};

#endif
