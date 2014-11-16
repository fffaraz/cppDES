#include "descbc.h"

DESCBC::DESCBC(ui64 key, ui64 iv) :
    des(key),
    iv(iv),
    last_block(iv)
{
}

ui64 DESCBC::encrypt(ui64 block)
{
    last_block = des.encrypt(block ^ last_block);
    return last_block;
}

ui64 DESCBC::decrypt(ui64 block)
{
    ui64 result = des.decrypt(block) ^ last_block;
    last_block = block;
    return result;
}

void DESCBC::reset()
{
    last_block = iv;
}
