#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    int64_t * data;
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
            printLongLongLine(*data);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func2()
{
    int64_t * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        if (data != NULL)
        {
            printLongLongLine(*data);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func3()
{
    int64_t * data;
    int64_t tmpData = 5LL;
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
        printLongLongLine(*data);
    }
}

static void func4()
{
    int64_t * data;
    int64_t tmpData = 5LL;
    if(GLOBAL_CONST_TRUE)
    {
        {
            data = &tmpData;
        }
    }
    if(GLOBAL_CONST_TRUE)
    {
        printLongLongLine(*data);
    }
}

void func5()
{
    func1();
    func2();
    func3();
    func4();
}
