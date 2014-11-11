#ifndef TESTS_H
#define TESTS_H

#include "des.h"

void test(ui64 input, ui64 key)
{
    DES des(key);

    ui64 result = des.encrypt(input);
    printf("E: %016llX\n", result);

    result = des.decrypt(result);
    printf("D: %016llX\n", result);
    printf("P: %016llX\n", input);
}

void test1()
{
    ui64 input  = 0x9474B8E8C73BCA7D;

    for (int i = 0; i < 16; i++)
    {
        if (i % 2 == 0)
        {
            input = DES::encrypt(input, input);
            printf("E: %016llX\n", input);
        }
        else
        {
            input = DES::decrypt(input, input);
            printf("D: %016llX\n", input);
        }
    }
}

void test2()
{
    ui64 input = 0x9474B8E8C73BCA7D;
    ui64 key   = 0x0000000000000000;
    printf("\n");
    test(input, key);
    printf("\n");
}

void test3()
{
    test(0x0000000000000000, 0x0000000000000000);
    test(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
}

void alltests()
{
    test1();
    test2();
    test3();
}

#endif // TESTS_H
