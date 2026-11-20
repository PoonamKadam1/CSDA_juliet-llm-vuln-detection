#include "std_testcase.h"

static void func1()
{
    short data;
    data = 0;
    data = 2;
    {
        data++;
        short result = data;
        printIntLine(result);
    }
}

static void func2()
{
    short data;
    data = 0;
    data = (short)RAND32();
    if (data < SHRT_MAX)
    {
        data++;
        short result = data;
        printIntLine(result);
    }
    else
    {
        printLine("data value is too large to perform arithmetic safely.");
    }
}

void func3()
{
    func1();
    func2();
}
