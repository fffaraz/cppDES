#include "cppdes/fileencryption.h"

#include <fstream>

FileEncryption::FileEncryption(ui64 key1, ui64 key2, ui64 key3)
    : des(key1, key2, key3, (ui64)0x0000000000000000)
{
}

int FileEncryption::encrypt(std::string input, std::string output)
{
    return cipher(input, output, false);
}

int FileEncryption::decrypt(std::string input, std::string output)
{
    return cipher(input, output, true);
}

int FileEncryption::cipher(std::string input, std::string output, bool mode)
{
    std::ifstream ifile;
    std::ofstream ofile;
    ui64 buffer;

    if (input.length() < 1)
        input = "/dev/stdin";
    if (output.length() < 1)
        output = "/dev/stdout";

    ifile.open(input, std::ios::binary | std::ios::in | std::ios::ate);
    ofile.open(output, std::ios::binary | std::ios::out);

    ui64 size = ifile.tellg();
    ifile.seekg(0, std::ios::beg);

    ui64 block = size / 8;
    if (mode)
        block--;

    for (ui64 i = 0; i < block; i++) {
        ifile.read((char*)&buffer, 8);

        if (mode)
            buffer = des.decrypt(buffer);
        else
            buffer = des.encrypt(buffer);

        ofile.write((char*)&buffer, 8);
    }

    if (mode == false) {
        // Amount of padding needed
        ui8 padding = 8 - (size % 8);

        // Padding cannot be 0 (pad full block)
        if (padding == 0)
            padding = 8;

        // Read remaining part of file
        buffer = (ui64)0;
        if (padding != 8)
            ifile.read((char*)&buffer, 8 - padding);

        // Pad block with a 1 followed by 0s
        ui8 shift = padding * 8;
        buffer <<= shift;
        buffer |= (ui64)0x0000000000000001 << (shift - 1);

        buffer = des.encrypt(buffer);
        ofile.write((char*)&buffer, 8);
    } else {
        // Read last line of file
        ifile.read((char*)&buffer, 8);
        buffer = des.decrypt(buffer);

        // Amount of padding on file
        ui8 padding = 0;

        // Check for and record padding on end
        while (!(buffer & 0x00000000000000ff)) {
            buffer >>= 8;
            padding++;
        }

        buffer >>= 8;
        padding++;

        if (padding != 8)
            ofile.write((char*)&buffer, 8 - padding);
    }

    ifile.close();
    ofile.close();
    return 0;
}
