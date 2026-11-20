#include "std_testcase.h"

static void func1()
{
    int * data;
    int func2[50];
    int func3[100];
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = func3;
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

static void func4()
{
    int * data;
    int func2[50];
    int func3[100];
    if(GLOBAL_CONST_TRUE)
    {
        data = func3;
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

void func5()
{
    func1();
    func4();
}
