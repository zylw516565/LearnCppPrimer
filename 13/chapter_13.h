#pragma once

#include <set>
#include <string>
#include <iostream>
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <memory>

using std::cout;
using std::endl;

using std::string;
using std::shared_ptr;
using std::unique_ptr;

class AAA
{
public:
    explicit AAA(const int a)
        :n(a)
    {}

//private:
    int n = 0;
};

struct WithArray
{
//     explicit WithArray(const int a[])
//         :array_(a)
//     {}

    int array_[5] = {0};
};


void testSynthesizedCopyConstructor()
{
    AAA a1(2);
    AAA a2(a1);
    cout << a1.n << " " << a2.n << endl;

    WithArray Array2;
    cout << Array2.array_  << endl;
    for (auto& elment : Array2.array_)
    {
        elment = 1;
    }

    WithArray Array3(Array2);
    cout << Array2.array_ << " " << Array3.array_ << endl;
}

void chapter_13()
{
    testSynthesizedCopyConstructor();
    system("pause");
}