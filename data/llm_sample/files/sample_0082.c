#include "std_testcase.h"

#include <math.h>

void func1()
{
    int data;
    data = 0;
    if(GLOBAL_CONST_TRUE)
    {
        data = RAND32();
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            int result = data * data;
            printIntLine(result);
        }
    }
}
