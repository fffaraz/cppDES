#include "des3.h"

DES3::DES3(ui64 k1, ui64 k2, ui64 k3) :
    des1(k1),
    des2(k2),
    des3(k3)
{
}

ui64 DES3::encrypt(ui64 block)
{
    return des3.encrypt(des2.decrypt(des1.encrypt(block)));
}

ui64 DES3::decrypt(ui64 block)
{
    return des1.decrypt(des2.encrypt(des3.decrypt(block)));
}
