#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    long * data;
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
            printLongLine(*data);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func2()
{
    long * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        if (data != NULL)
        {
            printLongLine(*data);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func3()
{
    long * data;
    long tmpData = 5L;
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
        printLongLine(*data);
    }
}

static void func4()
{
    long * data;
    long tmpData = 5L;
    if(GLOBAL_CONST_TRUE)
    {
        {
            data = &tmpData;
        }
    }
    if(GLOBAL_CONST_TRUE)
    {
        printLongLine(*data);
    }
}

void func5()
{
    func1();
    func2();
    func3();
    func4();
}
