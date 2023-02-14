#pragma once

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

void aboutString()
{
    vector<int> vecInt{1,2,3,4};
    for (auto& item : vecInt)
    {
        if (item == 4)
        {
            vecInt.push_back(5);
        }
        std::cout << item << std::endl;
    }


    vector<string> vecStr;
    vector<string>::iterator iter = vecStr.begin();

    const vector<string> cVecStr;
    vector<string>::const_iterator iterC = cVecStr.begin();
    //vector<string>::iterator iter3 = cVecStr.cbegin();

    std::string s;
    std::cin >> s;
    std::cout << s << std::endl;
}