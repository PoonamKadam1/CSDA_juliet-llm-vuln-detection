#include "std_testcase.h"

void func1()
{
    int * data;
    int func2[50];
    int func3[100];
    data = func2;
    {
        int source[100] = {0};
        memcpy(data, source, 100*sizeof(int));
        printIntLine(data[0]);
    }
}
