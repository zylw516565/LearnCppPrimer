#pragma once

#include <map>
#include <list>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

using std::string;
using std::map;

class NoDefault
{
public:
	//NoDefault() = default;
    NoDefault(const int& n) {}
	~NoDefault();
protected:
	
private:
};

void init()
{}

vector<int> vecInt(10,1);

std::list<string> names;
//vector<char> oldstyle;
vector<const char*> oldstyle;

//vector<NoDefault> vecNoDefault(10);

void VectorTest()
{
    vector<int> vec;
    for (int i = 0; i < 5; i++)
    {
        vec.push_back(i);
    }
    vector<int>::iterator it;
    cout << sizeof(it) << endl;
    for (it = vec.begin(); it != vec.end(); )
    {
#if 1
        if (*it > 2)
            it = vec.erase(it);
        else
            it++;
#else
        if (*it > 2)
            vec.erase(it);//此处会发生迭代器失效
#endif
    }
    for (it = vec.begin(); it != vec.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void mapTest()
{
    map<int, int>m;
    for (int i = 0; i < 10; i++)
    {
        m.insert(std::make_pair(i, i + 1));
    }
    map<int, int>::iterator it;

    for (it = m.begin(); it != m.end(); )
    {
        if (it->first == 5)
            m.erase(it++);
        it++;
    }
    for (it = m.begin(); it != m.end(); it++)
    {
        cout << (*it).first << " ";
    }
    cout << endl;
}

void testSizeAndCapacity()
{
    vector<int> ivec;
    cout << "ivec: size: " << ivec.size()
        << " ivec.capacity(): " << ivec.capacity() << endl;

    for (vector<int>::size_type ix = 0; ix != 24; ++ix)
        ivec.push_back(ix);

    cout << "ivec: size: " << ivec.size()
        << " ivec.capacity(): " << ivec.capacity() << endl;

    ivec.reserve(10);
    cout << "ivec: size: " << ivec.size()
        << " ivec.capacity(): " << ivec.capacity() << endl;

    ivec.reserve(50);
    cout << "ivec: size: " << ivec.size()
        << " ivec.capacity(): " << ivec.capacity() << endl;

    while (ivec.size() != ivec.capacity())
    {
        ivec.push_back(0);
    }
    cout << "ivec: size: " << ivec.size()
        << " ivec.capacity(): " << ivec.capacity() << endl;

    ivec.push_back(32);
    cout << "ivec: size: " << ivec.size()
        << " ivec.capacity(): " << ivec.capacity() << endl;

    ivec.shrink_to_fit();
    cout << "ivec: size: " << ivec.size()
        << " ivec.capacity(): " << ivec.capacity() << endl;

}

void testString()
{
    const char* cp = "Hello World!!!";
    char noNull[] = {'H', 'i'};
    string s1(cp);
    string s2(noNull, 2);
    string s3(noNull);
    string s4(cp+6, 5);
    string s5(s1, 6, 5);
    string s6(s1, 6);
    string s7(s1, 6, 20);
    //string s8(s1, 16);  //抛出异常
}

void chapter_9()
{
	//vector<NoDefault> v2(10, init);
	//vector<NoDefault> v2(10);
	auto b = vecInt.begin();
	//auto e = vecInt.end();
	auto e = b++;
	//vecInt.assign(b, e);

	names.assign(oldstyle.begin(), oldstyle.end());

    VectorTest();
    mapTest();
    testSizeAndCapacity();
    testString();
    system("pause");
}