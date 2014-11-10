#ifndef DES_H
#define DES_H

#include <cstdint>
using namespace std;

class DES
{
public:
    DES(uint64_t key);
    uint64_t encrypt(uint64_t block);
    uint64_t decrypt(uint64_t block);
    uint64_t des(uint64_t block, char mode);

private:
    uint64_t sub_key[16]; // 48 bits
    void keygen(uint64_t key);

    uint64_t ip(uint64_t block);
    uint64_t pi(uint64_t block);

    void feistel(uint32_t &L, uint32_t &R, uint32_t F);
    uint32_t f(uint32_t R, uint64_t k);

};

#endif // DES_H
