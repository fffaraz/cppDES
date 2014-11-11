#include <iostream>
using namespace std;

#include "des.h"

void test1()
{
    uint64_t input  = 0x9474B8E8C73BCA7D;

    for (uint8_t i = 0; i < 16; i++)
    {
        DES des(input);

        if (i % 2 == 0)
        {
            input = des.encrypt(input);
            printf("E: %016llX\n", input);
        }
        else
        {
            input = des.decrypt(input);
            printf("D: %016llX\n", input);
        }
    }
}

void test2()
{
    uint64_t input = 0x9474B8E8C73BCA7D;
    uint64_t key   = 0x0000000000000000;
    uint64_t result;

    DES des(key);

    printf("\nP: %016llX\n", input);

    result = des.encrypt(input);
    printf("E: %016llX\n", result);

    result = des.encrypt(result);
    printf("D: %016llX\n\n", result);
}

int main()
{
    test1();
    test2();
    return 0;
}

