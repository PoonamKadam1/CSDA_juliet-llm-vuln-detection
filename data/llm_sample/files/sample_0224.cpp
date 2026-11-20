#include "std_testcase.h"

namespace func1
{

static void func2()
{
    TwoIntsClass * data;
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
            delete data;
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func3()
{
    TwoIntsClass * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        if (data != NULL)
        {
            printIntLine(data->intOne);
            delete data;
        }
        else
        {
            printLine("data is NULL");
        }
    }
}

static void func4()
{
    TwoIntsClass * data;
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        {
            TwoIntsClass * tmpData = new TwoIntsClass;
            tmpData->intOne = 0;
            tmpData->intTwo = 0;
            data = tmpData;
        }
    }
    if(GLOBAL_CONST_TRUE)
    {
        printIntLine(data->intOne);
        delete data;
    }
}

static void func5()
{
    TwoIntsClass * data;
    if(GLOBAL_CONST_TRUE)
    {
        {
            TwoIntsClass * tmpData = new TwoIntsClass;
            tmpData->intOne = 0;
            tmpData->intTwo = 0;
            data = tmpData;
        }
    }
    if(GLOBAL_CONST_TRUE)
    {
        printIntLine(data->intOne);
        delete data;
    }
}

void func6()
{
    func2();
    func3();
    func4();
    func5();
}

}
