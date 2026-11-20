#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    twoIntsStruct * data;
    twoIntsStruct tmpData;
    {
        tmpData.intOne = 0;
        tmpData.intTwo = 0;
        data = &tmpData;
    }
    printIntLine(data->intOne);
}

static void func2()
{
    twoIntsStruct * data;
    data = NULL;
    if (data != NULL)
    {
        printIntLine(data->intOne);
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
