#include "des.h"
#include "des_data.h"

DES::DES(uint64_t key)
{
    keygen(key);
}

void DES::keygen(uint64_t key)
{
    // initial key schedule calculation
    uint64_t permuted_choice_1 = 0; // 56 bits
    for (uint8_t i = 0; i < 56; i++)
    {
        permuted_choice_1 <<= 1;
        permuted_choice_1 |= (key >> (64-PC1[i])) & LB64_MASK;
    }

    // 28 bits
    uint32_t C = (uint32_t) ((permuted_choice_1 >> 28) & 0x000000000fffffff);
    uint32_t D = (uint32_t) (permuted_choice_1 & 0x000000000fffffff);

    // Calculation of the 16 keys
    for (uint8_t i = 0; i < 16; i++)
    {
        // key schedule
        // shifting Ci and Di
        for (uint8_t j = 0; j < iteration_shift[i]; j++)
        {
            C = (0x0fffffff & (C << 1)) | (0x00000001 & (C >> 27));
            D = (0x0fffffff & (D << 1)) | (0x00000001 & (D >> 27));
        }

        uint64_t permuted_choice_2 = (((uint64_t) C) << 28) | (uint64_t) D ;

        sub_key[i] = 0;
        for (uint8_t j = 0; j < 48; j++)
        {
            sub_key[i] <<= 1;
            sub_key[i] |= (permuted_choice_2 >> (56-PC2[j])) & LB64_MASK;
        }
    }
}

uint64_t DES::encrypt(uint64_t block)
{
    return des(block, 'e');
}

uint64_t DES::decrypt(uint64_t block)
{
    return des(block, 'd');
}

uint64_t DES::encrypt(uint64_t block, uint64_t key)
{
    DES des(key);
    return des.des(block, 'e');
}

uint64_t DES::decrypt(uint64_t block, uint64_t key)
{
    DES des(key);
    return des.des(block, 'd');
}

uint64_t DES::des(uint64_t block, char mode)
{
    block = ip(block);

    uint32_t L = (uint32_t) (block >> 32) & L64_MASK;;
    uint32_t R = (uint32_t) (block & L64_MASK);

    for (uint8_t i = 0; i < 16; i++)
    {
        uint32_t F = (mode == 'd') ? f(R, sub_key[15-i]) : f(R, sub_key[i]);
        feistel(L, R, F);
    }

    block = (((uint64_t) R) << 32) | (uint64_t) L;
    block = pi(block);
    return block;
}

uint64_t DES::ip(uint64_t block)
{
    // initial permutation
    uint64_t result = 0;
    for (uint8_t i = 0; i < 64; i++)
    {
        result <<= 1;
        result |= (block >> (64-IP[i])) & LB64_MASK;
    }
    return result;
}

uint64_t DES::pi(uint64_t block)
{
    // inverse initial permutation
    uint64_t result = 0;
    for (uint8_t i = 0; i < 64; i++)
    {
        result <<= 1;
        result |= (block >> (64-PI[i])) & LB64_MASK;
    }
    return result;
}

void DES::feistel(uint32_t &L, uint32_t &R, uint32_t F)
{
    uint32_t temp = R;
    R = L ^ F;
    L = temp;
}

uint32_t DES::f(uint32_t R, uint64_t k)
{
    // f(R,k) function
    uint64_t s_input = 0;

    for (uint8_t j = 0; j < 48; j++)
    {

        s_input <<= 1;
        s_input |= (uint64_t) ((R >> (32-E[j])) & LB32_MASK);

    }

    // Encryption/Decryption
    // XORing expanded Ri with Ki
    s_input = s_input ^ k;

    // S-Box Tables
    uint32_t s_output;
    for (uint8_t j = 0; j < 8; j++)
    {
        // 00 00 RCCC CR00 00 00 00 00 00 s_input
        // 00 00 1000 0100 00 00 00 00 00 row mask
        // 00 00 0111 1000 00 00 00 00 00 column mask

        char row;
        row = (char) ((s_input & (0x0000840000000000 >> 6*j)) >> (42-6*j));
        row = (row >> 4) | (row & 0x01);

        char column = (char) ((s_input & (0x0000780000000000 >> 6*j)) >> (43-6*j));

        s_output <<= 4;
        s_output |= (uint32_t) (S[j][16*row + column] & 0x0f);
    }

    uint32_t result = 0;
    for (uint8_t j = 0; j < 32; j++)
    {
        result <<= 1;
        result |= (s_output >> (32 - P[j])) & LB32_MASK;
    }

    return result;
}
