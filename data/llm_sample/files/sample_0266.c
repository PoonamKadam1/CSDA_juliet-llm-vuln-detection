#include "std_testcase.h"

#include <wchar.h>

void func1()
{
    char * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printHexCharLine(data[0]);
    }
}
