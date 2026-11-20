#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    int64_t * data;
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = new int64_t[100];
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i] = 5LL;
            }
        }
        delete [] data;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printLongLongLine(data[0]);
    }
}

}
