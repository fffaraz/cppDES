#pragma once

#include <cstdint>

using ui64 = uint64_t;
using ui32 = uint32_t;
using ui8 = uint8_t;

class DES {
public:
    DES(ui64 key);
    ui64 des(ui64 block, bool mode);

    ui64 encrypt(ui64 block);
    ui64 decrypt(ui64 block);

    static ui64 encrypt(ui64 block, ui64 key);
    static ui64 decrypt(ui64 block, ui64 key);

protected:
    void keygen(ui64 key); // Key generation

    ui64 ip(ui64 block); // Initial Permutation
    ui64 fp(ui64 block); // Final Permutation

    void feistel(ui32& L, ui32& R, ui32 F); // Feistel function
    ui32 f(ui32 R, ui64 k); // F function

private:
    ui64 sub_key[16]; // 48 bits each
};
