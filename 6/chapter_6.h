#pragma once

#include <string>
#include <initializer_list>

using std::cout;
using std::endl;

using std::string;
using std::initializer_list;

// void printfunc(int &arr[10])
// {
//     for (auto elem : arr)
//         std::cout << elem << std::endl;
// }

void printfunc(int (&arr)[10])
{
    for (auto elem : arr)
        std::cout << elem << std::endl;
}

void err_msg(const initializer_list<string>& il)
{
    for (auto beg = il.begin(); beg != il.end(); ++ beg)
    {
        cout << *beg << " ";
    }
    cout << endl;
}

void foo6(int n, ...)
{
    cout << "n = " << n << endl;
}

void chapter_6()
{
    int i = 0, j[2] = {0, 1};
    int k[10] = { 0 };
//     printfunc(&i);
//     printfunc(j);
    printfunc(k);

    string expected("hello"), actual("world");
    if (expected != actual)
        err_msg({"functionX", expected, actual });
    else
        err_msg({"functionX", "ok"});

    foo6(3);

}