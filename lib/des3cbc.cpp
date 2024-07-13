#include "cppdes/des3cbc.h"

DES3CBC::DES3CBC(ui64 key1, ui64 key2, ui64 key3, ui64 iv)
    : des3(key1, key2, key3)
    , iv(iv)
    , last_block(iv)
{
}

ui64 DES3CBC::encrypt(ui64 block)
{
    last_block = des3.encrypt(block ^ last_block);
    return last_block;
}

ui64 DES3CBC::decrypt(ui64 block)
{
    ui64 result = des3.decrypt(block) ^ last_block;
    last_block = block;
    return result;
}

void DES3CBC::reset()
{
    last_block = iv;
}
