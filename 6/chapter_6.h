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

string &manip()
{
    string ret2("world !!!");
    string ret;
    ret.assign("hello");

    if (!ret.empty())
        return ret;   //错误, ret是一个局部临时量
    else
        return ret2;  //错误,"Empty"是一个局部临时量

}

char &get_val(string &str, string::size_type ix)
{
    return str[ix];
}

//void overload_test(string str)
//{
//    cout << str << endl;
//}
//
//void overload_test(const string str)
//{
//    cout << str << endl;
//}

void overload_test(string &str)
{
    cout << str << endl;
}

void overload_test(const string &str)
{
    cout << str << endl;
}

void overload_test(string *str)
{
    cout << *str << endl;
}

void overload_test(const string *str)
{
    cout << *str << endl;
}

const string& shorterString(const string &s1, const string& s2)
{
    return s1.size() <= s2.size() ? s1 : s2;
}

string& shorterString(string& s1, string& s2)
{
    auto& r = shorterString(const_cast<const string&>(s1), 
                            const_cast<const string&>(s2));
    return const_cast<string&>(r);
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

//     manip() = "nihao";
//     cout << "manip(): " << manip() << endl;
    string strVal("a value");
    cout << "strVal: " << strVal << endl;
    get_val(strVal, 0) = 'A';
    cout << "strVal: " << strVal << endl;

    string strNonConstVal("non const overload");
    const string strConstVal("const overload");
    overload_test(strNonConstVal);
    overload_test(strConstVal);
    overload_test(&strNonConstVal);
    overload_test(&strConstVal);

    string s1("nihao"), s2("nihao123");
    cout << "shorterString(): " << shorterString(s1, s2) << endl;
}