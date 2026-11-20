#include "std_testcase.h"

namespace func1
{

static void func2()
{
    TwoIntsClass * data;
    {
        TwoIntsClass * tmpData = new TwoIntsClass;
        tmpData->intOne = 0;
        tmpData->intTwo = 0;
        data = tmpData;
    }
    printIntLine(data->intOne);
    delete data;
}

static void func3()
{
    TwoIntsClass * data;
    data = NULL;
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

void func4()
{
    func2();
    func3();
}

}
