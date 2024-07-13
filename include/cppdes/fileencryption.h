#pragma once

#include <string>

#include "cppdes/des3cbc.h"

class FileEncryption {
public:
    FileEncryption(ui64 key1, ui64 key2, ui64 key3);
    int encrypt(std::string input, std::string output);
    int decrypt(std::string input, std::string output);
    int cipher(std::string input, std::string output, bool mode);

private:
    DES3CBC des;
};
