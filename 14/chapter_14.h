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

int add(int i, int j) { return i + j; }
auto mod = [](int i, int j) { return i % j; };
struct divide {
    int operator()(int i, int divisor){
        return i / divisor;
    }
};

void testFunction()
{
    std::function<int(int, int)> f3 = [](int i, int j){ return i * j; };
    cout << f3(4, 2) << endl;

    map<string, std::function<int(int, int)>> binops =
    {
        {"+", add},
        {"-", std::minus<int>()},
        {"/", divide()},
        {"*", [](int i, int j) { return i * j; }},
        {"%", mod},
    };

    cout << "binops[\" + \"](10, 5): " << binops["+"](10, 5) << endl;
    cout << "binops[\" - \"](10, 5): " << binops["-"](10, 5) << endl;
    cout << "binops[\" / \"](10, 5): " << binops["/"](10, 5) << endl;
    cout << "binops[\" * \"](10, 5): " << binops["*"](10, 5) << endl;
    cout << "binops[\" % \"](10, 5): " << binops["%"](10, 5) << endl;

}

class SmallInt
{
private:
    std::size_t val;
public:
    SmallInt(int i = 0)
        :val(i)
    {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad SmallInt value");
    }

//     int operator int() const;
//     operator int(int = 0) const;
//     operator int* () const { return 42; }

    operator int() const { return val; }

    operator SmallInt&() const {  }
};

//operator int(SmallInt&);
class SmallIntV2
{
private:
    std::size_t val;
public:
    SmallIntV2(int i = 0)
        :val(i)
    {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad SmallInt value");
    }

    explicit operator int() const { return val; }
};

void testSmallInt()
{
    SmallInt si;
    si = 4;
    si + 3;

    SmallIntV2 siv2;
    siv2 = 4;
    //siv2 + 3;
    static_cast<int>(siv2) + 3;
}

void chapter_14()
{
    testOperator();
    testFunction();
    testSmallInt();
}