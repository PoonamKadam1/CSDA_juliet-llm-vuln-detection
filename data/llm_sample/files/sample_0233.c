#include "std_testcase.h"

void func1()
{
    unsigned int data;
    data = 0;
    if(GLOBAL_CONST_TRUE)
    {
        data = UINT_MAX;
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            unsigned int result = data + 1;
            printUnsignedLine(result);
        }
    }
}
