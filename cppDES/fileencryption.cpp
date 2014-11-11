#include "fileencryption.h"

FileEncryption::FileEncryption(uint64_t key) :
    des(key, 0x0000000000000000)
{
}

int FileEncryption::encrypt(string input, string output)
{
    return cipher(input, output, false);
}

int FileEncryption::decrypt(string input, string output)
{
    return cipher(input, output, true);
}


int FileEncryption::cipher(string input, string output, bool mode)
{
    ifstream ifile;
    ofstream ofile;
    ui64 buffer;

    ifile.open(input,  ios::binary | ios::in | ios::ate);
    ofile.open(output, ios::binary | ios::out);

    int size = ifile.tellg();
    ifile.seekg(0, ios::beg);

    for (int i = 0; i < size / 8; i++)
    {
        ifile.read((char*) &buffer, 8);

        if(mode)
            buffer = des.decrypt(buffer);
        else
            buffer = des.encrypt(buffer);

        ofile.write((char*) &buffer, 8);
    }

    // Amount of padding needed
    int padding = 8 - (size % 8);

    /*
    // Padding cannot be 0 (pad full block)
    if (padding == 0)
        padding  = 8;
    */

    // Read remaining part of file
    buffer = 0;
    if(padding != 8)
        ifile.read((char*) &buffer, 8 - padding);

    /*
    // Pad block with a 1 followed by 0s
    buffer[8 - padding] = 1;
    for(int i = 1; i < padding; i++)
    {
        buffer[8 - i] = 0;
    }
    */

    if(mode)
        buffer = des.decrypt(buffer);
    else
        buffer = des.encrypt(buffer);

    ofile.write((char*) &buffer, 8);

    ifile.close();
    ofile.close();
    return 0;
}
