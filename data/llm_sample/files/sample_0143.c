#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    wchar_t * data;
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
            printWcharLine(data[0]);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func2()
{
    wchar_t * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        if (data != NULL)
        {
            printWcharLine(data[0]);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func3()
{
    wchar_t * data;
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = L"func4";
    }
    if(GLOBAL_CONST_TRUE)
    {
        printWcharLine(data[0]);
    }
}

static void func5()
{
    wchar_t * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = L"func4";
    }
    if(GLOBAL_CONST_TRUE)
    {
        printWcharLine(data[0]);
    }
}

void func6()
{
    func1();
    func2();
    func3();
    func5();
}
