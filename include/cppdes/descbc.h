#pragma once

#include "cppdes/des.h"

class DESCBC
{
public:
    DESCBC(ui64 key, ui64 iv);
    ui64 encrypt(ui64 block);
    ui64 decrypt(ui64 block);
    void reset();

private:
    DES des;
    ui64 iv;
    ui64 last_block;
};
