#include <iostream>
using namespace std;

#include "des.h"

int main()
{
    uint64_t input  = 0x9474B8E8C73BCA7D;
    uint64_t key    = 0x0000000000000000;
    uint64_t result = input;

    for (uint8_t i = 0; i < 16; i++)
    {
        DES des(result);

        if (i%2 == 0)
        {
            result = des.des(result, 'e');
            printf("E: %016llx\n", result);
        }
        else
        {
            result = des.des(result, 'd');
            printf("D: %016llx\n", result);
        }
    }

    printf("----\n");

    DES des(key);

    result = des.des(input, 'e');
    printf ("E: %016llx\n", result);

    result = des.des(result, 'd');
    printf ("D: %016llx\n", result);

    return 0;
}

