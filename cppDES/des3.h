#ifndef DES3_H
#define DES3_H

#include "des.h"

class DES3
{
public:
    DES3(ui64 k1, ui64 k2, ui64 k3);
    ui64 encrypt(ui64 block);
    ui64 decrypt(ui64 block);

private:
    DES des1;
    DES des2;
    DES des3;
};

#endif // DES3_H
