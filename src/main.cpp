#include "cppdes/fileencryption.h"

#include <iostream>

void usage()
{
    std::cout << "Usage: cppDES -e/-d key1 key2 key3 [input-file] [output-file]" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc < 5) {
        usage();
        return 1;
    }

    std::string enc_dec = argv[1];
    if (enc_dec != "-e" && enc_dec != "-d") {
        usage();
        return 2;
    }

    std::string input, output;
    if (argc > 5)
        input = argv[5];
    if (argc > 6)
        output = argv[6];

    ui64 key1 = strtoull(argv[2], nullptr, 16);
    ui64 key2 = strtoull(argv[3], nullptr, 16);
    ui64 key3 = strtoull(argv[4], nullptr, 16);

    FileEncryption fe(key1, key2, key3);

    if (enc_dec == "-e")
        return fe.encrypt(input, output);
    if (enc_dec == "-d")
        return fe.decrypt(input, output);

    return 0;
}
