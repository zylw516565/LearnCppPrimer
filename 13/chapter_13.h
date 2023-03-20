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

void f(vector<int> vec)
{
}

class Test1
{
#if 1
public:
#else
private:
#endif
    Test1(const int a)
        :n(a)
    {}

    Test1();

//     Test1& operator=(const AAA& rhs)
//     {}

    Test1& operator=(const Test1& rhs)
    {
        return *this;
    }

    //Test1& operator=(const Test1& rhs) = default;

    //~Test1(const int) {}
    //~Test1() = delete;
    ~Test1() = default;
    //~Test1();

    //private:
    int n = 0;
};

Test1::Test1() = default;

struct NoDtor
{
    NoDtor() = default;
    ~NoDtor() = delete;
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

    //f(19);
    f(vector<int>(10));

    Test1 objTest1(1);
    Test1 objTest2, objTest3;
    objTest2 = objTest3;

//     Test1* ptrTest1 = new Test1();
//     Test1* ptrTest2 = ptrTest1;
//     delete ptrTest1;
//     delete ptrTest2;

    //NoDtor objNoDtor;
    NoDtor* ptrNoDtor = new NoDtor();
    //delete ptrNoDtor;
}

class HasPtr
{
private:
    string* ps;
    int      i;

public:
    HasPtr(const string& s = string())
        :ps(new string(s)),
        i(0)
    {}

    HasPtr(const HasPtr& rhs)
    {
        i = rhs.i;
        ps = new string(*rhs.ps);
    }

    HasPtr& operator=(const HasPtr& rhs)
    {
#if 1
        if(&rhs == this)
            return *this;

        auto newp = new string(*rhs.ps);
        delete ps;
        ps = newp;
        i = rhs.i;
        return *this;
#else
        delete ps;
        ps = new string(*rhs.ps);
        i = rhs.i;
        return *this;
#endif
    }

    ~HasPtr() {delete ps;}

};

void testHasPtr()
{
    HasPtr objHasPtr;
    objHasPtr = objHasPtr;
}

void chapter_13()
{
    testSynthesizedCopyConstructor();
    testHasPtr();
    system("pause");
}