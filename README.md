cppDES
======

C++ implementation of Data Encryption Standard

DES, 3DES, DES ECB Mode, DES CBC Mode

The Data Encryption Standard (DES) has been a standard encryption method in the United States for a number of years. It is moderately secure. No easy ways have been found to crack it, although a brute-force approach, using expensive special-purpose equipment, is probably feasible.

When is compiled as a standalone application, it produces a command-line application that encrypts or decrypts a file using a hexadecimal key taken from the second command-line argument.

Usage: cppDES -e/-d key [input-file] [output-file]
