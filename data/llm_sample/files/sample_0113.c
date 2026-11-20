#include "std_testcase.h"

#include <math.h>

void func1()
{
    int data;
    data = 0;
    if(GLOBAL_CONST_TRUE)
    {
        fscanf(stdin, "%d", &data);
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            int result = data * data;
            printIntLine(result);
        }
    }
}
