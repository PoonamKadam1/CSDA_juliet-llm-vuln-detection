#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    char * data;
    data = "func2";
    printHexCharLine(data[0]);
}

static void func3()
{
    char * data;
    data = NULL;
    if (data != NULL)
    {
        printHexCharLine(data[0]);
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
