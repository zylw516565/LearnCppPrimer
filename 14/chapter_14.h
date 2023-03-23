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


void testOperator()
{
    string data1("hello "), data2("world !!!");
    auto data3 = &data1;
    *data3;
    data1 + data2;
    cout << "operator+(data1, data2): "
        << operator+(data1, data2)
        << endl;

    //data1 = operator=(data2);
    data1.operator=(data2);

    data1 += data2;
    data1.operator +=(data2);

    cout << "data1.operator +=(data2): "
        << data1
        << endl;

    string s = "word";
    string u = "hi" + s;
    //string u2 = "hi" + "world";
}


void chapter_14()
{
    testOperator();
    system("pause");
}