#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    int64_t * data;
    int64_t tmpData = 5LL;
    {
        data = &tmpData;
    }
    printLongLongLine(*data);
}

static void func2()
{
    int64_t * data;
    data = NULL;
    if (data != NULL)
    {
        printLongLongLine(*data);
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
