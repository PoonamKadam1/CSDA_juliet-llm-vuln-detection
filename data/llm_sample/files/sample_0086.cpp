#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    long * data;
    data = NULL;
    data = new long[100];
    {
        size_t i;
        for(i = 0; i < 100; i++)
        {
            data[i] = 5L;
        }
    }
    delete [] data;
    printLongLine(data[0]);
}

}
