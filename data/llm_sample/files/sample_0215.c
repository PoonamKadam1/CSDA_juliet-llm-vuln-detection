#include "std_testcase.h"

#include <math.h>

static void func1()
{
    int data;
    data = 0;
    if(GLOBAL_CONST_TRUE)
    {
        data = RAND32();
    }
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        if (data > INT_MIN && abs(data) < (long)sqrt((double)INT_MAX))
        {
            int result = data * data;
            printIntLine(result);
        }
        else
        {
            printLine("data value is too large to perform arithmetic safely.");
        }
    }
}

static void func2()
{
    int data;
    data = 0;
    if(GLOBAL_CONST_TRUE)
    {
        data = RAND32();
    }
    if(GLOBAL_CONST_TRUE)
    {
        if (data > INT_MIN && abs(data) < (long)sqrt((double)INT_MAX))
        {
            int result = data * data;
            printIntLine(result);
        }
        else
        {
            printLine("data value is too large to perform arithmetic safely.");
        }
    }
}

static void func3()
{
    int data;
    data = 0;
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = 2;
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            int result = data * data;
            printIntLine(result);
        }
    }
}

static void func4()
{
    int data;
    data = 0;
    if(GLOBAL_CONST_TRUE)
    {
        data = 2;
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            int result = data * data;
            printIntLine(result);
        }
    }
}

void func5()
{
    func1();
    func2();
    func3();
    func4();
}
