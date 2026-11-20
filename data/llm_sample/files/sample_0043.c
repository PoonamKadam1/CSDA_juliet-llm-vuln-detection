#include "std_testcase.h"

#include <wchar.h>

void func1()
{
    long * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printLongLine(*data);
    }
}
