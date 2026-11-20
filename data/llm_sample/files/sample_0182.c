#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    wchar_t * data;
    data = L"func2";
    printWcharLine(data[0]);
}

static void func3()
{
    wchar_t * data;
    data = NULL;
    if (data != NULL)
    {
        printWcharLine(data[0]);
    }
    else
    {
        printLine("data is NULL");
    }
}

void func4()
{
    func1();
    func3();
}
