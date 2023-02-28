#pragma once

#include <string>
#include <iostream>

using std::cout;
using std::endl;

using std::string;

class Chapter7
{
private:
    int value;
    int *ptr;
    string str;
public:
//     Chapter7()const
//     {}

     Chapter7(int tmp)
     {}

};

class A
{
private:
    int a;
    Chapter7 chapter7;

};

class Sales_data
{
    friend std::istream& read(std::istream& is, Sales_data& item)
    {
        is >> item.protectedBookNo;

        double price = 0;
        is >> item.bookNo >> item.units_sold >> price >> item.protectedBookNo;
        item.revenue = price * item.units_sold;
        return is;
    }

public:
	Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p)
        :bookNo(s),units_sold(n), revenue(p*n)
    {}
    Sales_data(const std::string& s) :bookNo(s){}
    Sales_data(std::istream& s){}

    std::string isbn()const { return bookNo; }
    Sales_data &combine(const Sales_data&)
    {}

    /*inline */void test_inline();

    void some_member() const
    {
        //++access_ctr2;
        ++access_ctr;
    }


protected:
    std::string protectedBookNo;
private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    mutable int access_ctr = 0;
    int access_ctr2 = 0;
};

inline void Sales_data::test_inline()
{
}

std::istream& read(std::istream& is, Sales_data& item);


void readStream(std::istream& is)
{
}

void chapter_7()
{
    readStream(std::cin);
    int tmp;
    int *pTmp;
    cout << "tmp = " << tmp << " pTmp = " << pTmp << endl;

    //A a;

    Sales_data item;
    read(std::cin, item);

}