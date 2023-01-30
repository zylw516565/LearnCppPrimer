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

    unsigned char c = -1;
    std::cout << "unsigned char c = " << (int)c << std::endl;

}