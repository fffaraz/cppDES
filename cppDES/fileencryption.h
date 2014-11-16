#ifndef FILEENCRYPTION_H
#define FILEENCRYPTION_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "descbc.h"

class FileEncryption
{
public:
    FileEncryption(ui64 key);
    int encrypt(string input, string output);
    int decrypt(string input, string output);
    int cipher (string input, string output, bool mode);

private:
    DESCBC des;
};

#endif // FILEENCRYPTION_H
