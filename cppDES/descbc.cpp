#include "descbc.h"

DESCBC::DESCBC(uint64_t key, uint64_t iv) :
    des(key),
    last_block(iv)
{
}

ui64 DESCBC::encrypt(uint64_t block)
{
    last_block = des.encrypt(block ^ last_block);
    return last_block;
}

ui64 DESCBC::decrypt(uint64_t block)
{
    last_block = des.decrypt(block ^ last_block);
    return last_block;
}
