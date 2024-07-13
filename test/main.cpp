#include "cppdes/des.h"
#include "cppdes/des3.h"
#include "cppdes/descbc.h"

#include <cstdio>
#include <gtest/gtest.h>

void test(ui64 input, ui64 key)
{
    DES des(key);
    ui64 output = des.encrypt(input);
    ui64 input2 = des.decrypt(output);

    printf("%016lX -> %016lX -> %016lX \n", input, output, input2);
    EXPECT_EQ(input, input2);
}

TEST(cppDESTest, Test1)
{
    ui64 input = 0x9474B8E8C73BCA7D;
    for (int i = 0; i < 16; i++) {
        if (i % 2 == 0) {
            input = DES::encrypt(input, input);
            printf("E: %016lX\n", input);
        } else {
            input = DES::decrypt(input, input);
            printf("D: %016lX\n", input);
        }
    }
}

TEST(cppDESTest, Test2)
{
    ui64 input = 0x9474B8E8C73BCA7D;
    ui64 key = 0x0000000000000000;
    test(input, key);
}

TEST(cppDESTest, Test3)
{
    test(0x0000000000000000, 0x0000000000000000);
    test(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
}

TEST(cppDESTest, Test4)
{
    DES3 des(0x2BD6459F82C5B300, 0x952C49104881FF48, 0x2BD6459F82C5B300);
    ui64 input = 0x8598538A8ECF117D;

    ui64 result = des.encrypt(input);
    printf("E: %016lX\n", result);
    EXPECT_EQ(result, 0xEA024714AD5C4D84);

    result = des.decrypt(result);
    printf("D: %016lX\n", result);
    printf("P: %016lX\n", input);
    EXPECT_EQ(result, input);
}

TEST(cppDESTest, Test5)
{
    DESCBC des(0xFFFFFFFFFFFFFFFF, 0x0000000000000000);

    ui64 input1 = 0x0000000000000000;
    ui64 input2 = 0x0000000000000000;
    ui64 input3 = 0x0000000000000000;

    ui64 output1 = des.encrypt(input1);
    ui64 output2 = des.encrypt(input2);
    ui64 output3 = des.encrypt(input3);

    printf("P1: %016lX -> E1: %016lX \n", input1, output1);
    printf("P2: %016lX -> E2: %016lX \n", input2, output2);
    printf("P3: %016lX -> E3: %016lX \n", input3, output3);

    EXPECT_EQ(output1, 0xCAAAAF4DEAF1DBAE);
    EXPECT_EQ(output2, 0x0000000000000000);
    EXPECT_EQ(output3, 0xCAAAAF4DEAF1DBAE);
}
