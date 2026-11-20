#include "std_testcase.h"

#include <math.h>

void func1()
{
    char data;
    data = ' ';
    if(GLOBAL_CONST_TRUE)
    {
        data = CHAR_MAX;
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            char result = data * data;
            printHexCharLine(result);
        }
    }
}
