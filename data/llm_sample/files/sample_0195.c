#include "std_testcase.h"

static void func1()
{
    short data;
    data = 0;
    data = 2;
    if(data > 0)
    {
        short result = data * 2;
        printIntLine(result);
    }
}

static void func2()
{
    short data;
    data = 0;
    fscanf (stdin, "%hd", &data);
    if(data > 0)
    {
        if (data < (SHRT_MAX/2))
        {
            short result = data * 2;
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
