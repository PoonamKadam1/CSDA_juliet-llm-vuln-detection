#include "std_testcase.h"

static void func1()
{
    int64_t data;
    data = 0LL;
    data = 2;
    {
        data++;
        int64_t result = data;
        printLongLongLine(result);
    }
}

static void func2()
{
    int64_t data;
    data = 0LL;
    data = LLONG_MAX;
    if (data < LLONG_MAX)
    {
        data++;
        int64_t result = data;
        printLongLongLine(result);
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
