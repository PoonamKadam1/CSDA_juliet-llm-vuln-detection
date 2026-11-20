#include "std_testcase.h"

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
            int result = data + 1;
            printIntLine(result);
        }
    }
}
