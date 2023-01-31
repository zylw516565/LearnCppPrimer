#pragma once

#include <iostream>

void convert()
{
    bool b = 42;
    std::cout << "b = " << b << std::endl;

    int i = b;
    std::cout << "i = " << i << std::endl;

    i = 3.14;
    std::cout << "i = " << i << std::endl;

    double pi = 3;
    std::cout << "pi = " << pi << std::endl;

    float pi2 = 100.;
    std::cout << "pi2 = " << pi2 << " izeof(pi2) = " << sizeof(pi2) << std::endl;

    float pi3 = 4.0 * 3.0;
    std::cout << "pi3 = " << pi3 << std::endl;

    double pi4 = 430000000000000001;
    printf("%f can be written %e\n", pi4, pi4);

    unsigned char c = -1;
    std::cout << "unsigned char (int)c = " << (int)c << " unsigned char c = " << c << std::endl;
    printf("hex unsigned char c = %x\n", c);

    char signedC = -1;
    std::cout << " signedC = " << (signed char)signedC << std::endl;
    printf("hex char c = %x\n", signedC);

    unsigned short ushortC = -1;
    std::cout << "ushortC = " << ushortC << " sizeof ushortC = " << sizeof ushortC << std::endl;
    printf("hex ushortC = %x\n", ushortC);

    unsigned int uintC = -1;
    std::cout << "uintC = " << uintC << " sizeof uintC = " << sizeof uintC << std::endl;
    printf("hex uintC = %x\n", uintC);

    unsigned long long ullC = -1;
    std::cout << "ullC = " << ullC << " sizeof ullC = " << sizeof ullC << std::endl;
    printf("hex ullC = %llx\n", ullC);

    signed char c2 = 256;
    std::cout << "signed char c2 = " << c2 << std::endl;
    std::cout << "signed char c2 = " << (int)c2 << std::endl;

    signed char c3 = 16;
    std::cout << "signed char c3 = " << c3 << std::endl;

    unsigned u = 10;
    int inum = -42;
    std::cout << inum + inum << std::endl;
    std::cout << u + inum  << std::endl;
    std::cout << u*inum << std::endl;

    unsigned u1 = 43; unsigned u2 = 10;
    std::cout << u1 - u2  << std::endl;
    std::cout << u2 - u1 << std::endl;

    int iN = 20;
    std::cout << iN << std::endl;
    iN = 020;
    std::cout << iN << std::endl;
    iN = 024;
    std::cout << iN << std::endl;
    iN = 0x14;
    std::cout << iN << std::endl;
    iN = 0x15;
    std::cout << iN << std::endl;

//     for (unsigned u = 10; u >= 0; --u)
//     {
//         std::cout << u << std::endl;
//     }

    std::cout << '\?' << std::endl;
    std::cout << "a really, really long string literal that spans two lines ' " << std::endl;

    int iVar__;
    int ___VVVar;

}