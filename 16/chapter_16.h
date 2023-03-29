#pragma once

#include <set>
#include <string>
#include <iostream>
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <memory>
#include <functional>


using std::cout;
using std::endl;

using std::string;
using std::shared_ptr;
using std::unique_ptr;

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

void testCompare()
{
    cout << "compare(3, 1): " << compare(3, 1) << endl;
    cout << "compare<int>(3, 1): " << compare<int>(3, 1) << endl;

    cout << "compare(\"hi\", \"mom\"): " << compare("hi", "mom") << endl;

}

//Ç°ÖÃÉùÃ÷
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
};

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

void testBlob()
{
    Blob<string> strBlob({ "a", "an", "the" });
    Blob<string> strBlob2 = {"a", "an", "the"};
}

void chapter_16()
{
    testCompare();
    testBlob();
}