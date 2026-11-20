#include "std_testcase.h"

static void func1()
{
    unsigned int data;
    data = 0;
    data = 2;
    {
        unsigned int result = data + 1;
        printUnsignedLine(result);
    }
}

static void func2()
{
    unsigned int data;
    data = 0;
    fscanf (stdin, "%u", &data);
    if (data < UINT_MAX)
    {
        unsigned int result = data + 1;
        printUnsignedLine(result);
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
