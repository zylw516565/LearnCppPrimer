#pragma once

#include <string>

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

}