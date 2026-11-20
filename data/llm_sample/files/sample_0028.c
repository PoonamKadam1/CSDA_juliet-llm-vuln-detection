#include "std_testcase.h"

#include <wchar.h>

void func1()
{
    int64_t * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printLongLongLine(*data);
    }
}
