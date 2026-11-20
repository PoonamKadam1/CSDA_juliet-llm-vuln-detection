#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    long * data;
    long tmpData = 5L;
    {
        data = &tmpData;
    }
    printLongLine(*data);
}

static void func2()
{
    long * data;
    data = NULL;
    if (data != NULL)
    {
        printLongLine(*data);
    }
    else
    {
        printLine("data is NULL");
    }
}

void func3()
{
    func1();
    func2();
}
