#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    int * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        if (data != NULL)
        {
            printIntLine(*data);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func2()
{
    int * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        if (data != NULL)
        {
            printIntLine(*data);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func3()
{
    int * data;
    int tmpData = 5;
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        {
            data = &tmpData;
        }
    }
    if(GLOBAL_CONST_TRUE)
    {
        printIntLine(*data);
    }
}

static void func4()
{
    int * data;
    int tmpData = 5;
    if(GLOBAL_CONST_TRUE)
    {
        {
            data = &tmpData;
        }
    }
    if(GLOBAL_CONST_TRUE)
    {
        printIntLine(*data);
    }
}

void func5()
{
    func1();
    func2();
    func3();
    func4();
}
