#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    twoIntsStruct * data;
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
            printIntLine(data->intOne);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func2()
{
    twoIntsStruct * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        if (data != NULL)
        {
            printIntLine(data->intOne);
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func3()
{
    twoIntsStruct * data;
    twoIntsStruct tmpData;
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        {
            tmpData.intOne = 0;
            tmpData.intTwo = 0;
            data = &tmpData;
        }
    }
    if(GLOBAL_CONST_TRUE)
    {
        printIntLine(data->intOne);
    }
}

static void func4()
{
    twoIntsStruct * data;
    twoIntsStruct tmpData;
    if(GLOBAL_CONST_TRUE)
    {
        {
            tmpData.intOne = 0;
            tmpData.intTwo = 0;
            data = &tmpData;
        }
    }
    if(GLOBAL_CONST_TRUE)
    {
        printIntLine(data->intOne);
    }
}

void func5()
{
    func1();
    func2();
    func3();
    func4();
}
