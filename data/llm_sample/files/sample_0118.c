#include "std_testcase.h"

static void func1()
{
    int data;
    data = 0;
    if(GLOBAL_CONST_TRUE)
    {
        data = INT_MAX;
    }
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        if (data < INT_MAX)
        {
            ++data;
            int result = data;
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
        data = INT_MAX;
    }
    if(GLOBAL_CONST_TRUE)
    {
        if (data < INT_MAX)
        {
            ++data;
            int result = data;
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
            ++data;
            int result = data;
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
            ++data;
            int result = data;
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
