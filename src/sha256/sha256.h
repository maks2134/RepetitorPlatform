#ifndef SHA256_H
#define SHA256_H

#include <cstddef>
#include <array>

class SHA256 {
public:
    static const size_t BLOCK_SIZE = 32;

    SHA256();
    void update(const unsigned char* data, size_t len);
    void final(unsigned char hash[BLOCK_SIZE]);

private:
    using BYTE = unsigned char;
    using WORD = unsigned int;

    std::array<BYTE, 64> data;
    WORD datalen;
    unsigned long long bitlen;
    std::array<WORD, 8> state;

    static const std::array<WORD, 64> k;
    void transform(const BYTE data[]);
    static WORD rotRight(WORD a, WORD b);
    static WORD choose(WORD x, WORD y, WORD z);
    static WORD majority(WORD x, WORD y, WORD z);
    static WORD ep0(WORD x);
    static WORD ep1(WORD x);
    static WORD sig0(WORD x);
    static WORD sig1(WORD x);
};

#endif // SHA256_H