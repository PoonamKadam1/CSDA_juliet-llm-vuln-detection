#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    int * data;
    data = NULL;
    data = new int[100];
    {
        size_t i;
        for(i = 0; i < 100; i++)
        {
            data[i] = 5;
        }
    }
    delete [] data;
    printIntLine(data[0]);
}

}
