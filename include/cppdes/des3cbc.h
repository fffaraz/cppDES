#pragma once

#include "cppdes/des3.h"

// Triple DES in CBC mode
class DES3CBC {
public:
    DES3CBC(ui64 key1, ui64 key2, ui64 key3, ui64 iv);
    ui64 encrypt(ui64 block);
    ui64 decrypt(ui64 block);
    void reset();

private:
    DES3 des3;
    ui64 iv;
    ui64 last_block;
};
