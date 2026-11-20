#include "std_testcase.h"

static void func1()
{
    int * data;
    int func2[50];
    int func3[100];
    data = func3;
    {
        int source[100] = {0};
        memcpy(data, source, 100*sizeof(int));
        printIntLine(data[0]);
    }
}

void func4()
{
    func1();
}
