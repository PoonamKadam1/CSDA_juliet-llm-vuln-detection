#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    long * data;
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = new long;
        *data = 5L;
        delete data;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printLongLine(*data);
    }
}

}
