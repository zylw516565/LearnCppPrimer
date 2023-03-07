#pragma once

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

using std::string;
using std::map;

void testEqual()
{
    vector<string> roster1{"ni", "hao", "1" };
    std::list<const char*> roster2{ "ni", "hao", "12" };

    if (roster2.size() >= roster1.size())
    {
        bool bIsEqual = std::equal(roster1.cbegin(), roster1.cend(), roster2.cbegin());
        if (bIsEqual)
            cout << "roster1 is equal roster2" << endl;
        else
            cout << "roster1 is not equal roster2" << endl;
    }

}

void testEqualWithInvalidSize()
{
    vector<string> roster1{ "ni", "hao", "1", "2" };
    std::list<const char*> roster2{ "ni", "hao", "1" };

    bool bIsEqual = std::equal(roster1.cbegin(), roster1.cend(), roster2.cbegin());
    if (bIsEqual)
        cout << "roster1 is equal roster2" << endl;
    else
        cout << "roster1 is not equal roster2" << endl;
}

void printVec(const vector<int> vec)
{
    for (const auto& elment : vec)
    {
        cout << elment << " ";
    }
    cout << endl;
}

void testFill()
{
    vector<int> vec(20, 1);
    cout << "before fill vec: " << endl; printVec(vec);
    fill(vec.begin(), vec.end(), 0);
    cout << "1 after fill vec: " << endl; printVec(vec);
    fill(vec.begin(), vec.begin()+ vec.size()/2, 10);
    cout << "2 after fill vec: " << endl; printVec(vec);
}

void printArray(const int *array, const int size)
{
    for (int i=0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void testCopy()
{
    int a1[] = {0,1,2,3,4,5,6,7,8,9};
    int a2[sizeof(a1)/sizeof(*a1)];
    cout << "before copy, a1: "; printArray(a1, sizeof(a1)/sizeof(int)); cout << " a2: "; printArray(a2, sizeof(a2)/sizeof(int));
    auto ret = std::copy(std::begin(a1), std::end(a1), a2);
    cout << "after copy, a1: ";  printArray(a1, sizeof(a1) / sizeof(int)); cout << " a2: "; printArray(a2, sizeof(a2)/sizeof(int));
}

bool isShorter(const string &s1, const string& s2)
{
    return s1.size() < s2.size();
}

vector<string> words{"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};

void testSortAndUnique(vector<string> &words)
{
    std::sort(words.begin(), words.end());
    auto uni_red = std::unique(words.begin(), words.end());
    words.erase(uni_red, words.end());

    //std::stable_sort(words.begin(), words.end(), isShorter);
    std::stable_sort(words.begin(), words.end(), 
                     [](const string& a, const string& b)
                     {return a.size() < b.size(); });
}

void testLambda()
{
    //auto f = [] {return 42; };
    auto f = [] { return 45; cout << "hello" << endl; };
    cout << "f(): " << f() << endl;

    vector<int> vi;
    std::transform(vi.begin(), vi.end(), vi.begin(),
        [](int i) {return i < 0 ? -i : i; });

    std::transform(vi.begin(), vi.end(), vi.begin(),
        [](int i) 
        {
            if (i < 0)
                return -i; 
            else 
                return i; 
        }
    );

    std::transform(vi.begin(), vi.end(), vi.begin(),
        [](int i) -> int
        {
            if (i < 0)
                return -i;
            else
                return i;
        }
    );
}

void bigges(vector<string>& words, const string::size_type sz)
{
    testSortAndUnique(words);

    auto wc = std::find_if(words.begin(), words.end(),
        [sz](const string& a){return a.size() >= sz; }
    );

    auto count = words.end() - wc;
    cout << count << " " << sz << endl;

    for_each(wc, words.end(), [](const string& a) {cout << a << " "; });
    cout << endl;
}

void chapter_10()
{
    testEqual();
    //testEqualWithInvalidSize();
    testFill();
    testCopy();
    testLambda();
    bigges(words, 5);
    system("pause");
}