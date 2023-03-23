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

class AAA
{
public:
    explicit AAA(const int a)
        :n(a)
    {}

//private:
    int n = 0;
};

struct WithArray
{
//     explicit WithArray(const int a[])
//         :array_(a)
//     {}

    int array_[5] = {0};
};

void f(vector<int> vec)
{
}

class Test1
{
#if 1
public:
#else
private:
#endif
    Test1(const int a)
        :n(a)
    {}

    Test1();

//     Test1& operator=(const AAA& rhs)
//     {}

    Test1& operator=(const Test1& rhs)
    {
        return *this;
    }

    //Test1& operator=(const Test1& rhs) = default;

    //~Test1(const int) {}
    //~Test1() = delete;
    ~Test1() = default;
    //~Test1();

    //private:
    int n = 0;
};

Test1::Test1() = default;

struct NoDtor
{
    NoDtor() = default;
    ~NoDtor() = delete;
};

void testSynthesizedCopyConstructor()
{
    AAA a1(2);
    AAA a2(a1);
    cout << a1.n << " " << a2.n << endl;

    WithArray Array2;
    cout << Array2.array_  << endl;
    for (auto& elment : Array2.array_)
    {
        elment = 1;
    }

    WithArray Array3(Array2);
    cout << Array2.array_ << " " << Array3.array_ << endl;

    //f(19);
    f(vector<int>(10));

    Test1 objTest1(1);
    Test1 objTest2, objTest3;
    objTest2 = objTest3;

//     Test1* ptrTest1 = new Test1();
//     Test1* ptrTest2 = ptrTest1;
//     delete ptrTest1;
//     delete ptrTest2;

    //NoDtor objNoDtor;
    NoDtor* ptrNoDtor = new NoDtor();
    //delete ptrNoDtor;
}

class HasPtr
{
private:
    string* ps;
    int      i;

public:
    HasPtr(const string& s = string())
        :ps(new string(s)),
        i(0)
    {}

    HasPtr(const HasPtr& rhs)
    {
        i = rhs.i;
        ps = new string(*rhs.ps);
    }

    HasPtr& operator=(const HasPtr& rhs)
    {
#if 1
        if(&rhs == this)
            return *this;

        auto newp = new string(*rhs.ps);
        delete ps;
        ps = newp;
        i = rhs.i;
        return *this;
#else
        delete ps;
        ps = new string(*rhs.ps);
        i = rhs.i;
        return *this;
#endif
    }

    ~HasPtr() {delete ps;}

};

class LikePtr
{
private:
    string* ps;
    int      i;
    std::size_t* use;

public:

    friend void swap(LikePtr&, LikePtr&);

    LikePtr(const string& s = string())
        :ps(new string(s)),
        i(0),
        use(new std::size_t(1))
    {}

    LikePtr(const LikePtr& rhs)
        :ps(rhs.ps),
        i(rhs.i),
        use(rhs.use)
    {
        ++(*use);
    }

    LikePtr& operator=(const LikePtr& rhs)
    {
        if (this == &rhs)
            return *this;

        ++(*rhs.use);
        if (!--(*use))
        {
            delete ps;
            delete use;
        }

        ps = rhs.ps;
        i = rhs.i;
        use = rhs.use;

        return *this;
    }

    LikePtr& operator=(LikePtr rhs)
    {
        swap(*this, rhs);
        return *this;
    }

    ~LikePtr()
    {
        if (!--(*use))
        {
            delete ps;
            delete use;
        }
    }
};

inline void swap(LikePtr& lhs, LikePtr& rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);

//     auto tmpps = lhs.ps;
//     lhs.ps = rhs.ps;
//     rhs.ps = tmpps;
// 
//     auto tmpi = lhs.i;
//     lhs.i = rhs.i;
//     rhs.i = tmpi;
}

void testHasPtr()
{
    HasPtr objHasPtr;
    objHasPtr = objHasPtr;
}

class StrVec
{
private:
    string* elements = nullptr;
    string* first_free = nullptr;
    string* cap = nullptr;
    static std::allocator<string> alloc;

public:
    StrVec() :elements(nullptr),
        first_free(nullptr),
        cap(nullptr)
    {}

    StrVec(const StrVec& rhs)
    {
    }

    StrVec& operator=(const StrVec& rhs)
    {
        cout << "operator=" << endl;
        return *this;
    }

    StrVec(StrVec &&rhs) noexcept
        :elements(rhs.elements),
        first_free(rhs.first_free),
        cap(rhs.cap)
    {
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }

    StrVec& operator=(StrVec&& rhs) noexcept
    {
        if (this != &rhs) {
            free();
            elements = rhs.elements;
            first_free = rhs.first_free;
            cap = rhs.cap;
            rhs.elements = rhs.first_free = rhs.cap = nullptr;
        }
        return *this;
    }


    ~StrVec()
    {
        free();
    }

    void push_back(const std::string& s)
    {
        chk_n_alloc();
        alloc.construct(first_free++, s);
    }

    std::size_t size() const { return first_free - elements;}
    std::size_t capacity() const { return cap - elements; }


    void testnoexcept() noexcept;

private:
    void alloc_n_copy(const StrVec& rhs)
//         string* elements,
//         string* first_free,
//         string* cap)
    {
        if (nullptr    == rhs.elements
            || nullptr == rhs.first_free
            || nullptr == rhs.cap)
            return;

        auto rhsbegin = rhs.elements;
        auto size = rhs.first_free - rhs.elements;
        auto capSize = rhs.cap - rhs.elements;
        elements = alloc.allocate(rhs.cap - rhs.elements);
        first_free = elements + size;
        cap = elements + capSize;
        auto begin = elements;

        while (begin <= first_free)
        {
            alloc.construct(begin++, *(rhsbegin++));
        }

        //std::copy(elements, first_free, dest);
    }

    void free()
    {
        if (elements){
            for (auto begin = first_free; begin != elements; )
                alloc.destroy(--begin);

            alloc.deallocate(elements, cap - elements);
        }
    }

    void chk_n_alloc()
    {
        if(size() >= capacity())
            reallocate();
    }

    void reallocate()
    {
        auto size = first_free - elements;
        auto capSize = cap - elements;
        auto newElements = alloc.allocate(capSize * 2);
        auto newbegin = newElements;
        while (elements <= first_free)
        {
            alloc.construct(newbegin++, *elements++);
        }

        free();
        elements = newElements;
        first_free = newElements + size;
        cap = newElements + capSize;
    }

};

std::allocator<string> StrVec::alloc;

void StrVec::testnoexcept() noexcept
{
}

StrVec getStrVec()
{
    return StrVec();
}

void testStrVec()
{
    StrVec objStrVec; const StrVec cstrVec;
    objStrVec.size();
    cstrVec.size();

    StrVec v1, v2;
    v1 = v2;
    v2 = getStrVec();
}

using std::move;

void testRValue()
{
    int i = 42;
    int &r = i;
    //int&& rr = i;
    //int &r2 = i * 42;
    const int &r3 = i * 42;
    int &&rr2 = i * 42;

    //变量是左值,变量可以看成变量表达式
    int &&rr3 = 42;
    //int &&rr4 = r3;
    rr3 = 3;
    cout << "rr3: " << rr3 << endl;
    int&& rr4 = move(rr3);
    //int &&rr4 = std::move(rr3);
    std::cout << "rr4: " << rr4 << endl;
}

struct TestMoveCtor1
{
    TestMoveCtor1() = default;

    TestMoveCtor1(const TestMoveCtor1& rhs)
        :n_(rhs.n_)
    {
    }

    int n_ = 0;
};

void testMoveCtor()
{
    TestMoveCtor1 objTestMoveCtor1; objTestMoveCtor1.n_ = 1;
    TestMoveCtor1 objTestMoveCtor2 = std::move(objTestMoveCtor1);
}

void chapter_13()
{
    testSynthesizedCopyConstructor();
    testHasPtr();
    testStrVec();
    testRValue();
    system("pause");
}