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

int getSize()
{
    return 2;
}

void testDynamicArray()
{
    int* pia  = new int[10];
    int* pia2 = new int[10]();

    int* pia3 = new int[2]{0,1};

    int n = getSize();
    try
    {
        int* pia4 = new int[n] {0, 1, 2};
    }
    catch (std::exception e)
    {
    }
    catch (...)
    {
        cout << "... exception:" << endl;
    }

    int* pia5 = nullptr;
    delete pia5;

    shared_ptr<int[]> sp(new int[10], [](int* p) {delete []p; });
    cout << "sp[0]: " << sp[0] << endl;
    for (size_t i = 0; i < 10; ++i)
    {
        *(sp.get() + i) = i;
    }
    for (size_t i=0; i < 10; ++i)
    {
        cout << *(sp.get() + i) << " ";
    }
    cout << endl;

    sp.reset();

    unique_ptr<int []> up(new int[10]);
    cout << "up[0]: " << up[0] << endl;

    up.release();

}

void testAllocator()
{
    int n = 3;
    std::allocator<string> alloc;
    auto const p = alloc.allocate(n);
    auto q = p;
    alloc.construct(q++);
    alloc.construct(q++, 10, 'c');
    alloc.construct(q++, "hi");
    cout << *p << " "; cout << *(p+1) << " ";
    cout << endl;
    //cout << *q << endl;  //灾难: q指向未构造的内存
}

class TextQuery
{
private:
    std::vector<string> inputText_;
    std::map<string, std::set<int>> wordLineNoMap_;

public:
    TextQuery(std::ifstream& infile)
    {}

    void query(const string& s)
    {
    }
};

// ostream &print(ostream &os)
// {
// }

void runQueries(std::ifstream &infile)
{
    //infile是一个ifstream,指向我们要处理的文件
    TextQuery tq(infile);  //保存文件并建立查询map
    //与用户交互: 提示用户输入要查询的单词,完成查询并打印结果

    while (true){
        cout << "enter word to look for, or q to quit: " << endl;
        string s;
        if(!(std::cin >> s) || "q" == s) break;

        //print(cout, tq.query(s)) << endl;
    }
}

void chapter_12()
{
    testCircularReference();
    testDynamicArray();
    testAllocator();
    system("pause");
}