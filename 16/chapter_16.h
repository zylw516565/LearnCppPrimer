#pragma once

#include <set>
#include <string>
#include <iostream>
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <memory>
#include <functional>
#include <list>
#include <vector>

using std::cout;
using std::endl;

using std::string;
using std::shared_ptr;
using std::unique_ptr;

using std::vector;
using std::ostream;
using std::ostringstream;


template <typename T>
int compare(const T& v1, const T& v2)
{
    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

// template <>
// int compareV2(const int& v1, const int& v2)
// {
// }

// template <typename T, U>
// T calc(const T&, const U&);

template <typename T, class U> T calc(const T&, const U&);

template <unsigned N, unsigned M>
int compare(const char(&p1)[N], const char(&p2)[M])
{
    return strcmp(p1, p2);
}

//inline template <typename T> T min(const T&, const T&);
template <typename T> inline T min(const T&, const T&);

template <typename T, typename F = less<T>>
int compare(const T& v1, const T& v2, F f=F())
{
    if (f(v1, v2)) return -1;
    if (f(v2, v1)) return 1;
    return 0;
}

template <typename A, typename B>
int flexibleCompare(const A& v1, const B& v2)
{
    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

template <typename T> ostream& print(ostream& os, const T &obj)
{
    return os << obj;
}

void testCompare()
{
    cout << "compare(3, 1): " << compare(3, 1) << endl;
    cout << "compare<int>(3, 1): " << compare<int>(3, 1) << endl;

    cout << "compare(\"hi\", \"mom\"): " << compare("hi", "mom") << endl;

    long lng;
    //compare(lng, 1024);
    compare<long>(lng, 1024);
    compare<int>(lng, 1024);
    flexibleCompare(lng, 1024);

    print(cout, 42);
    std::ofstream f("output");
    print(f, 10);
}

//前置声明
template<typename> class BlobPtr;
template<typename> class Blob;

template<typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

template<typename T>
class Blob
{
public:
    typedef typename std::vector<T>::size_type size_type;

    friend class BlobPtr<T>;
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
private:
    std::shared_ptr<std::vector<T>> data;

#if 1
    void check(size_type i, const string& msg) const;
#else
    void check(size_type i, const string& msg) const
    {
        if (i >= data->size())
            throw std::out_of_range(msg);
    }
#endif

public:
    Blob()
        :data(std::make_shared<std::vector<T>>())
    {}

    Blob(std::initializer_list<T> il)
        :data(std::make_shared<std::vector<T>>(il))
    {}

    template <typename It> Blob(It b, It e);

    size_type size() { return data->size(); }
    bool empty() { return data->empty(); }
    void push_back(const T& t) { data->push_back(t); }
    void push_back(T&& t) { data->push_back(std::move(t)); }
    void pop_back()
    {
        check(0, "pop_back on empty Blob");
        data->pop_back();
    }

    T& front()
    {
        check(0, "front on empty Blob");
        return data->front();
    }

    T& back()
    {
        check(0, "back on empty Blob");
        return data->back();
    }

    T& operator[](size_type i)
    {
        check(i, "subscript out of range");
        return (*data)[i];
    }
};

template <typename T>
template <typename It>
Blob<T>::Blob(It b, It e)
    :data(std::make_shared<std::vector<T>>(b, e))
{}

template <typename T>
void Blob<T>::check(size_type i, const string& msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template<typename T>
class BlobPtr
{
};

template <typename T> class Pal;
class C
{
    friend class Pal<C>;
    template <typename T> friend class Pal2;
};

template <typename T> class C2
{
    friend class Pal<T>;
    template <typename X> friend class Pal3;
    friend class Pal4;
};

template<typename Type> class Bar
{
    friend Type;
};

typedef Bar<int> BarInt;

template <typename T> using twin = std::pair<T, T>;
twin<string> authors;
twin<int> win_loss;
twin<double> area;

template <typename T> using twin2 = std::pair<T, int>;

template <typename T>
class Foo2
{
public:
    std::size_t size() { return ctr; }
private:
    static std::size_t ctr;
};

template <typename T>
std::size_t Foo2<T>::ctr = 0;

class StaticTest
{
public:
    StaticTest()
    {}

    int getTmp() { return tmp; }

private:
    static int tmp;
};

int StaticTest::tmp = 1;

typedef double A2;
template <typename A2, typename B> void f(A2 a, B b)
{
    A2 tmp = a;
    //double B; GCC下会报错, VC++不报错
}

//template <typename T, typename T> class Foo3;

template <typename T>
typename T::value_type top(const T& c)
{
    if (!c.empty())
        return c.back();
    else
        return typename T::value_type();
}

template <typename T = int>
class Numbers
{
private:
    T val;
public:
    Numbers(T v = 0)
        :val(v)
    {}
};

void testBlob()
{
    Blob<string> strBlob({ "a", "an", "the" });
    Blob<string> strBlob2 = {"a", "an", "the"};

    Foo2<int> objFoo2;
    objFoo2.size();
    StaticTest objStaticTest;
    cout << "objStaticTest.getTmp(): " << objStaticTest.getTmp() << endl;

    top<vector<int>>(vector<int>());

    Numbers<long double> lots_of_precision;
    Numbers<> average_precision;

    int ia[] = {0,1,2,3,4,5,6,7,8,9};
    vector<long> vi = { 0,1,2,3,4,5,6,7,8,9 };
    std::list<const char*> w = { "a", "an", "the" };
    Blob<int> a1(std::begin(ia), std::end(ia));
    Blob<int> a2(vi.begin(), vi.end());
    Blob<string> a3(w.begin(), w.end());
}

class DebugDelete
{
private:
    std::ostream &os;
public:
    DebugDelete(std::ostream& s = std::cerr):os(s) {}

    template <typename T>
    void operator()(T *p) const
    {
        os << "delete unique_ptr" << endl;
        delete p;
    }
};

template <typename T> T fobj(T t1, T t2)
{
    cout << "fobj: " << t1 << " " << t2 << endl;
    return T();
}

template <typename T> T fref(const T& t1, const T& t2)
{
    cout << "fref: " << t1 << " " << t2 << endl;
    return T();
}

void testDebugDelete()
{
    double* p = new double;
    DebugDelete d;
    d(p);

    int* ip = new int;
    DebugDelete()(ip);

    unique_ptr<int, DebugDelete> up(new int, DebugDelete());
    unique_ptr<string, DebugDelete> sp(new string, DebugDelete());

    string s1("a value");
    const string s2("another value");
    fobj(s1, s2);
    fref(s1, s2);

    int a[10], b[42];
    fobj(a, b);
    //fref(a, b);  错误:数组类型不匹配
}

template <typename T1, typename T2, typename T3>
T1 sum(T2, T3)
{
    return T1();
}

template <typename It>
auto fcn(It beg, It end)->decltype(*beg)
{
    return *beg;
}

template <typename It>
auto fcn2(It beg, It end)-> typename std::remove_reference<decltype(*beg)>::type
{
    return *beg;
}

template <typename T> void f1(T& p) {}
template <typename T> void f2(const T& p) {}
template <typename T> void f3(T&&) {}

void testSum()
{
    sum<int>(1, 2);

    vector<int> vi = { 0,1,2,3,4,5,6,7,8,9 };
    std::list<string> ca = { "a", "an", "the" };
    auto& i = fcn(vi.begin(), vi.end());
    auto& s = fcn(ca.begin(), ca.end());

    auto i2 = fcn2(vi.begin(), vi.end());
    int n = 0;
    const int cn = 0;
    f1(n);
    f1(cn);
    //f1(42);

    f2(n);
    f2(cn);
    f2(42);

    f3(n);
    f3(cn);
    f3(42);

    f3(std::move(n));   //被推断为: void f3(int&) {}
    f3(std::move(cn));  //被推断为: void f3(const int&) {}
    f3(std::move(42));  //被推断为: void f3(int&&) {}
}

template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2)
{
    f(t2, t1);
}
template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

void f(int v1, int &v2)
{
    cout << v1 << " " << ++v2 << endl;
}

void g(int &&v1, int& v2)
{
    cout << v1 << " " << ++v2 << endl;
}

void testFlip()
{
    int i = 0, j = 3;
    f(42, i);
    flip1(f, j , 42);
    flip2(f, j, 42);
    flip2(g, j, 42);
}

template <typename T> string debug_rep(const T& t)
{
    ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T> string debug_rep(T *p)
{
    ostringstream ret;
    ret << "pointer: " << p;
    if (p)
        ret << " " << *p;
    else
        ret << "null ptr";
    return ret.str();
}

string debug_rep(const string& s)
{
    return '"' + s + '"';
}

string debug_rep(const char* s)
{
    return debug_rep(string(s));
}

string debug_rep(char* s)
{
    return debug_rep(string(s));
}

void testDebugRep()
{
    string s("hi");
    cout << debug_rep(s) << endl;
    cout << debug_rep(&s) << endl;
    const string* sp = &s;
    cout << debug_rep(sp) << endl;

    string s2("hello");
    cout << debug_rep(s2) << endl;
    cout << debug_rep("hi world!") << endl;
    char ch[] = "hello";
    cout << debug_rep(ch) << endl;
}

template <typename T, typename... Args>
void foo(const T&, const Args&... rest) {}

template <typename ... Args> void g(Args ... args)
{
    cout << "sizeof...(Args) " << sizeof...(Args) << endl;
    cout << "sizeof...(args) " << sizeof...(args) << endl;
}

void testVariadicTemplate()
{
    int i = 0; double d = 3.14; string s("how");
    foo(i, s, 42, d);
    foo(s, 42, "hi");
    foo(d, s);
    foo("hi");
    g(i, s, 42, d);
}

template <typename T>
ostream& print2(ostream &os, const T& t)
{
    return os << t;
}

template <typename T, typename ... Args>
ostream& print2(ostream& os, const T& t, const Args&... rest)
{
    os << t << ", ";
    return print2(os, rest...);
}

void testPrint2()
{
    int i = 0; double d = 3.14; string s("how");
    print2(cout, i, s, 42);
}

void chapter_16()
{
    testCompare();
    testBlob();
    testDebugDelete();
    testSum();
    testFlip();
    testDebugRep();
    testVariadicTemplate();
    testPrint2();
}