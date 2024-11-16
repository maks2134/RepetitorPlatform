#include "sha256.h"
#include <memory.h>

// Constants
const std::array<SHA256::WORD, 64> SHA256::k = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Constructor
SHA256::SHA256() {
    datalen = 0;
    bitlen = 0;
    state = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
              0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
}

void SHA256::update(const BYTE* data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        this->data[datalen] = data[i];
        datalen++;
        if (datalen == 64) {
            transform(this->data.data());
            bitlen += 512;
            datalen = 0;
        }
    }
}

void SHA256::final(BYTE hash[BLOCK_SIZE]) {
    size_t i = datalen;

    // Pad remaining data
    if (datalen < 56) {
        data[i++] = 0x80;
        while (i < 56)
            data[i++] = 0x00;
    } else {
        data[i++] = 0x80;
        while (i < 64)
            data[i++] = 0x00;
        transform(data.data());
        memset(data.data(), 0, 56);
    }

    bitlen += datalen * 8;
    data[63] = bitlen;
    data[62] = bitlen >> 8;
    data[61] = bitlen >> 16;
    data[60] = bitlen >> 24;
    data[59] = bitlen >> 32;
    data[58] = bitlen >> 40;
    data[57] = bitlen >> 48;
    data[56] = bitlen >> 56;
    transform(data.data());

    // Convert to big endian
    for (i = 0; i < 4; ++i) {
        hash[i]      = (state[0] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 4]  = (state[1] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 8]  = (state[2] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 12] = (state[3] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 16] = (state[4] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 20] = (state[5] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 24] = (state[6] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 28] = (state[7] >> (24 - i * 8)) & 0x000000ff;
    }
}

void SHA256::transform(const BYTE data[]) {
    WORD a, b, c, d, e, f, g, h, t1, t2;
    std::array<WORD, 64> m;

    for (WORD i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
    for (WORD i = 16; i < 64; ++i)
        m[i] = sig1(m[i - 2]) + m[i - 7] + sig0(m[i - 15]) + m[i - 16];

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];

    for (WORD i = 0; i < 64; ++i) {
        t1 = h + ep1(e) + choose(e, f, g) + k[i] + m[i];
        t2 = ep0(a) + majority(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

// Helper functions
inline SHA256::WORD SHA256::rotRight(WORD a, WORD b) {
    return (a >> b) | (a << (32 - b));
}

inline SHA256::WORD SHA256::choose(WORD x, WORD y, WORD z) {
    return (x & y) ^ (~x & z);
}

inline SHA256::WORD SHA256::majority(WORD x, WORD y, WORD z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

inline SHA256::WORD SHA256::ep0(WORD x) {
    return rotRight(x, 2) ^ rotRight(x, 13) ^ rotRight(x, 22);
}

inline SHA256::WORD SHA256::ep1(WORD x) {
    return rotRight(x, 6) ^ rotRight(x, 11) ^ rotRight(x, 25);
}

inline SHA256::WORD SHA256::sig0(WORD x) {
    return rotRight(x, 7) ^ rotRight(x, 18) ^ (x >> 3);
}

inline SHA256::WORD SHA256::sig1(WORD x) {
    return rotRight(x, 17) ^ rotRight(x, 19) ^ (x >> 10);
}