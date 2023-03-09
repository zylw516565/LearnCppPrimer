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

    auto ret = word_count.insert({ "Jason",1 });
    if (!ret.second){
        ++((ret.first)->second);
    }
    auto ret2 = word_count.insert({"Peter",1});

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

void testSet()
{
    set<int> iset = {0,1,2,3,4,5,6,7,8,9};
    decltype(iset)::iterator set_it = iset.begin();
    if (set_it != iset.end()){
        //*set_it = 42;  //错误: set中的关键字是只读的
        cout << *set_it << endl;
    }

    set<int> iset2 = { 9,0,1,3,4,6,8,7,5,2};
    set_it = iset2.begin();
    while (set_it != iset2.end()) {
        cout << *set_it << endl;
        ++set_it;
    }
    cout << endl;

    vector<int> ivec = {2,4,6,8,2,4,6,8};

//     set<string> set3;
//     set3.insert(ivec.cbegin(), ivec.cend());

    set<int> set2;
    set2.insert(ivec.cbegin(), ivec.cend());
    set2.insert({1,3,5,7,1,3,5,7});
}

void chapter_11()
{
    initSetAndMultiset();
    testMap();
    testSet();
    system("pause");
}