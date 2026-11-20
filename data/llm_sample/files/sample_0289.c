#include "std_testcase.h"

static void func1()
{
    int data;
    data = 0;
    data = 2;
    if(data > 0)
    {
        int result = data * 2;
        printIntLine(result);
    }
}

static void func2()
{
    int data;
    data = 0;
    data = INT_MAX;
    if(data > 0)
    {
        if (data < (INT_MAX/2))
        {
            int result = data * 2;
            printIntLine(result);
        }
        else
        {
            printLine("data value is too large to perform arithmetic safely.");
        }
    }
}

void func3()
{
    func1();
    func2();
}
