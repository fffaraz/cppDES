#ifndef DES_H
#define DES_H

#include <cstdint>
using namespace std;

#define ui64 uint64_t
#define ui32 uint32_t
#define ui8  uint8_t

class DES
{
public:
    DES(ui64 key);
    ui64 des(ui64 block, char mode);

    ui64 encrypt(ui64 block);
    ui64 decrypt(ui64 block);

    static ui64 encrypt(ui64 block, ui64 key);
    static ui64 decrypt(ui64 block, ui64 key);

protected:
    void keygen(ui64 key);

    ui64 ip(ui64 block);
    ui64 pi(ui64 block);

    void feistel(uint32_t &L, uint32_t &R, uint32_t F);
    uint32_t f(uint32_t R, ui64 k);

private:
    ui64 sub_key[16]; // 48 bits
};

#endif // DES_H
