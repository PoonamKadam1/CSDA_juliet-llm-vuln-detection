#include "std_testcase.h"

#include <wchar.h>

void func1()
{
    twoIntsStruct * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printIntLine(data->intOne);
    }
}
