#include "std_testcase.h"

#include <math.h>

void func1()
{
    char data;
    data = ' ';
    if(GLOBAL_CONST_TRUE)
    {
        data = (char)RAND32();
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            char result = data * data;
            printHexCharLine(result);
        }
    }
}
