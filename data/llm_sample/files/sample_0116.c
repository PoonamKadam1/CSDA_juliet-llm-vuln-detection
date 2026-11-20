#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    char * data;
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
            printHexCharLine(data[0]);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func2()
{
    char * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        if (data != NULL)
        {
            printHexCharLine(data[0]);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func3()
{
    char * data;
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = "func4";
    }
    if(GLOBAL_CONST_TRUE)
    {
        printHexCharLine(data[0]);
    }
}

static void func5()
{
    char * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = "func4";
    }
    if(GLOBAL_CONST_TRUE)
    {
        printHexCharLine(data[0]);
    }
}

void func6()
{
    func1();
    func2();
    func3();
    func5();
}
