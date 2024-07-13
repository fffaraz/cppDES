#pragma once

#include <string>

#include "cppdes/descbc.h"

class FileEncryption
{
public:
    FileEncryption(ui64 key);
    int encrypt(std::string input, std::string output);
    int decrypt(std::string input, std::string output);
    int cipher (std::string input, std::string output, bool mode);

private:
    DESCBC des;
};
