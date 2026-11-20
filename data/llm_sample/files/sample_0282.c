#include "std_testcase.h"

void func1()
{
    int * data;
    int func2[50];
    int func3[100];
    if(GLOBAL_CONST_TRUE)
    {
        data = func2;
    }
    {
        int source[100] = {0};
        {
            size_t i;
            for (i = 0; i < 100; i++)
            {
                data[i] = source[i];
            }
            printIntLine(data[0]);
        }
    }
}
