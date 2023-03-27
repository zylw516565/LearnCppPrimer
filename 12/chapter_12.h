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

using TextVecType = std::vector<string>;

using LineNoSet    = std::set<unsigned>;
using LineNoSetPtr = std::shared_ptr<LineNoSet>;
using WordLineNoMapType = std::map<string, LineNoSetPtr>;

struct QueryResult
{
//     explicit QueryResult()
//         :word_(""),
//         lineNo_(0),
//         inputText_(nullptr),
//         wordLineNoMap_(nullptr)
//     {
//     }

    bool     isFind = false;
    string   word_  = "";
    std::shared_ptr<TextVecType> inputText_;
    LineNoSetPtr                 lineNoSet_;

    void print(std::ostream &os)
    {
        if (!isFind)
        {
            os << word_ << " dose not exsit !!!" << endl;
            return;
        }

        if (lineNoSet_ && inputText_)
        {
            os << word_ << ":" << endl;
            for (const auto& lineNo : *lineNoSet_)
            {
                os << (lineNo + 1) << " " << inputText_->at(lineNo) << endl;
            }
        }
        else
        {
            os << "Error: null ptr !!!" << endl;
        }
    }
};

class TextQuery
{
private:
    std::shared_ptr<TextVecType> inputText_;
    std::shared_ptr<WordLineNoMapType> wordLineNoMap_;

public:
    TextQuery(std::ifstream& infile)
        :inputText_(std::make_shared<TextVecType>(TextVecType())),
        wordLineNoMap_(std::make_shared<WordLineNoMapType>(WordLineNoMapType()))
    {
        parseInputFile(infile);
    }

    const std::shared_ptr<QueryResult> query(const string& word)
    {
        std::shared_ptr<QueryResult> sp(std::make_shared<QueryResult>(QueryResult()));
        sp->word_ = word;
        sp->inputText_ = inputText_;
        auto iter = wordLineNoMap_->find(word);
        if (iter != wordLineNoMap_->end())
        {
            sp->isFind = true;
            sp->lineNoSet_ = iter->second;
        }
        else
        {
            sp->isFind = false;
            sp->lineNoSet_ = nullptr;
        }

        return sp;
    }

private:
    void parseInputFile(std::ifstream& infile)
    {
        string line; unsigned lineNo = 0;
        while (std::getline(infile, line))
        {
            inputText_->emplace_back(line);

            string word;
            std::istringstream stream(line);
            while (stream >> word)
            {
                auto iter = wordLineNoMap_->find(word);
                if (iter != wordLineNoMap_->end())
                    iter->second->insert(lineNo);
                else
                    wordLineNoMap_->insert(make_pair(word, std::make_shared<LineNoSet>(LineNoSet{ lineNo })));
            }

            lineNo++;
        }
    }
};

std::ostream& print(std::ostream &os, const std::shared_ptr<QueryResult>& qr)
{
    qr->print(os);
    return os;
}

void runQueries(std::ifstream &infile)
{
    //infile是一个ifstream,指向我们要处理的文件
    TextQuery tq(infile);  //保存文件并建立查询map
    //与用户交互: 提示用户输入要查询的单词,完成查询并打印结果

    while (true){
        cout << "enter word to look for, or q to quit: " << endl;
        string s;
        if(!(std::cin >> s) || "q" == s) break;

        print(cout, tq.query(s)) << endl;
    }
}

void testQueries()
{
    std::ifstream input("./12/input.txt");

    if (!input.is_open())
    {
        std::cerr << "input.is_open failed !" << endl;
        return;
    }

    runQueries(input);
}

class StrBlob
{
public:
    typedef std::vector<string>::size_type size_type;
private:
    std::shared_ptr<std::vector<string>> data;
    void check(size_type i, const string &msg) const
    {
        if (i >= data->size())
            throw std::out_of_range(msg);
    }

public:
    StrBlob()
        :data(std::make_shared<std::vector<string>>())
    {}

    StrBlob(std::initializer_list<string> il)
        :data(std::make_shared<std::vector<string>>(il))
    {}

    size_type size() { return data->size(); }
    bool empty() { return data->empty(); }
    void push_back(const string& t) { data->push_back(t); }
    void pop_back()
    {
        check(0, "pop_back on empty StrBlob");
        data->pop_back();
    }

    string& front()
    {
        check(0, "front on empty StrBlob");
        return data->front();
    }

    string& back()
    {
        check(0, "back on empty StrBlob");
        return data->back();
    }
};

void chapter_12()
{
    testCircularReference();
    testDynamicArray();
    testAllocator();
    testQueries();
    system("pause");
}