#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    int * data;
    int tmpData = 5;
    {
        data = &tmpData;
    }
    printIntLine(*data);
}

static void func2()
{
    int * data;
    data = NULL;
    if (data != NULL)
    {
        printIntLine(*data);
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
