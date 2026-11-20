#include "std_testcase.h"

void func1()
{
    int data;
    data = 0;
    if(GLOBAL_CONST_TRUE)
    {
        data = INT_MAX;
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            ++data;
            int result = data;
            printIntLine(result);
        }
    }
}
