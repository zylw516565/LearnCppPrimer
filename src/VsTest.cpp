#include "VsTest.h"

#include <iostream>


#include "../1/item_io.h"
#include "../1/add_item.h"

#include "../2/convert.h"
#include "../3/aboutString.h"
#include "../6/chapter_6.h"

using  std::cout;
using  std::endl;

int main()
{
    cout << "hello world!!!" << endl;

    //item_io();
    //add_item();
    //convert();
    //aboutString();
    chapter_6();

    getchar();
    return 0;
}