#include <iostream>
using namespace std;

#include "tests.h"
#include "fileencryption.h"

void usage()
{
    cout << "Usage: cppDES -e/-d key input-file output-file" << endl;
}

int main(int argc, char **argv)
{
    alltests(); return 0;

    if(argc < 3)
    {
        usage();
        return 1;
    }

    string enc_dec = argv[1];
    string input = "-";
    string output = input;

    if(enc_dec != "-e" && enc_dec != "-d")
    {
        usage();
        return 2;
    }

    if(argc > 3)
        input  = argv[3];
    if(argc > 4)
        output = argv[4];

    string strkey = argv[2];
    ui64 key = stoi(strkey, nullptr, 16);

    FileEncryption fe(key);

    if(enc_dec == "-e")
        fe.encrypt(input, output);
    if(enc_dec == "-d")
        fe.decrypt(input, output);

    return 0;
}
