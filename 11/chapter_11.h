#pragma once

#include <set>
#include <string>
#include <iostream>


using std::cout;
using std::endl;

using std::string;
using std::map;
using std::set;

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

void testMap()
{
    map<string, size_t> word_count{ {"Tom",21}, {"Jason",23} };

    cout << "for 1" << endl;
    for(const auto &w : word_count)
    {
        cout << w.first << " " << w.second << endl;
    }

    cout << "for 2" << endl;

    for (auto it = word_count.begin(); it != word_count.end(); ++it)
    {
        cout << (*it).first << " " << (*it).second << endl;
    }

    cout << "for 3" << endl;

    for (auto it = word_count.begin(); it != word_count.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
        //it->first = "new key";  //错误,关键字是const的
        ++it->second;
    }

    set<string>::value_type        v1;
    set<string>::key_type          v2;
    map<string, int>::value_type   v3;
    map<string, int>::key_type     v4;
    map<string, int>::mapped_type  v5;
}

void chapter_11()
{
    initSetAndMultiset();
    testMap();
    system("pause");
}