#pragma once

#include <set>
#include <string>
#include <iostream>
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <stdexcept>

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

    ++word_count["Jerry"];
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

//     const map<string, size_t> word_countV2{ {"Tom",21}, {"Jason",23} };
//     word_countV2["Jerry"];

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

void testMultimap()
{
    std::multimap<string, string> authors;
    authors.insert({"Barth, John", "Sot-"});
    authors.insert({ "Barth, John", "Lost in the Funhouse" });
    authors.insert({ "Barth, John", "AAA" });
    authors.insert({ "Peter", "BBB" });

    auto begin = authors.begin();
    while (begin != authors.end())
    {
        cout << begin->first << " " << begin->second << endl;
        ++begin;
    }
    cout << endl;

    //1 way
    string strSearchItem("Barth, John");
    auto entries = authors.count(strSearchItem);    //元素数量
    auto iter = authors.find(strSearchItem);
    while (entries)
    {
        cout << iter->first << " " << iter->second << endl;
        entries--;
        iter++;
    }
    cout << endl;

    //2 way
    begin = authors.lower_bound(strSearchItem);
    auto end = authors.upper_bound(strSearchItem);
    while (begin != end)
    {
        cout << begin->first << " " << begin->second << endl;
        begin++;
    }
    cout << endl;

    //3 way
    auto ret = authors.equal_range(strSearchItem);
    while (ret.first != ret.second)
    {
        cout << ret.first->first << " " << ret.first->second << endl;
        ret.first++;
    }
    cout << endl;

}

const map<string, string> buildMap(std::ifstream& map_file)
{
    map<string, string> transMap;

    string line;
    while (std::getline(map_file, line))
    {
        auto pos = line.find_first_of(" ");
        if (pos < 1)
            throw std::runtime_error("no rule !!!");
        else
        {
            auto key = line.substr(0, pos);
            auto value = line.substr(pos + 1);
            transMap[key] = value;
        }
    }

    return transMap;
}

const string transform(const string& orig_word, const map<string, string>& trans_map)
{
    auto iter = trans_map.find(orig_word);

    if (iter != trans_map.end())
        return iter->second;
    else
        return orig_word;
}

void wordTransform(std::ifstream& map_file, std::ifstream& input)
{
    auto trans_map = buildMap(map_file);

    string text;
    
    while (std::getline(input, text))
    {
        std::istringstream stream(text);
        string word;
        bool firstword = true;
        while (stream >> word)
        {
            if (firstword)
                firstword = false;
            else
                cout << " ";

            cout << transform(word, trans_map);
        }
        cout << endl;
    }
}

void testWordTransform()
{

    std::ifstream map_file("./11/map_file.txt");
    std::ifstream input("./11/input.txt");

    if (!map_file.is_open())
    {
        std::cerr << "map_file.is_open failed !" << endl;
        return;
    }

    if (!input.is_open())
    {
        std::cerr << "input.is_open failed !" << endl;
        return;
    }

    wordTransform(map_file, input);
}

void chapter_11()
{
    initSetAndMultiset();
    testMap();
    testSet();
    testMultimap();
    testWordTransform();
    system("pause");
}