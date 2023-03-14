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

class BB;

class AA
{
public:
    shared_ptr<BB> m_b;
};

class BB
{
public:
    shared_ptr<AA> m_a;
};

void testCircularReference()
{
    int count = 3;
    while (count)
    {
        shared_ptr<AA> a(new AA);
        shared_ptr<BB> b(new BB);

        a->m_b = b;
        b->m_a = a;

        count--;
    }

}

void chapter_12()
{
    testCircularReference();
    system("pause");
}