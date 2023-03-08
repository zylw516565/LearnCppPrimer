#pragma once

#include <set>
#include <string>
#include <iostream>


using std::cout;
using std::endl;

using std::string;
using std::map;

void initSetAndMultiset()
{
    vector<int> ivec;
    for (int i=0; i < 10; ++i)
    {
        ivec.push_back(i);
        ivec.push_back(i);
    }
    for (const auto& item : ivec)
    {
        cout << item << " ";
    }
    cout << endl;

    std::set<int> iset(ivec.cbegin(), ivec.cend());
    std::multiset<int> miset(ivec.cbegin(), ivec.cend());
    cout << ivec.size() << endl;
    cout << iset.size() << endl;
    cout << miset.size() << endl;
}

void chapter_11()
{
    initSetAndMultiset();
    system("pause");
}