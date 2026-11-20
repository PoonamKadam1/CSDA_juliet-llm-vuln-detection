#include "std_testcase.h"

#include <wchar.h>

void func1()
{
    wchar_t * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printWcharLine(data[0]);
    }
}
