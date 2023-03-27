#pragma once

#include <set>
#include <string>
#include <iostream>
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <memory>
#include <functional>


using std::cout;
using std::endl;

using std::string;
using std::shared_ptr;
using std::unique_ptr;

template <typename T>
int compare(const T& v1, const T& v2)
{
    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

// template <>
// int compareV2(const int& v1, const int& v2)
// {
// }

void testCompare()
{
    cout << "compare(3, 1): " << compare(3, 1) << endl;
    cout << "compare<int>(3, 1): " << compare<int>(3, 1) << endl;
}

void chapter_16()
{
    testCompare();
}