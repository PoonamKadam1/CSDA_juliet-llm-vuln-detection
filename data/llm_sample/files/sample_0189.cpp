#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

static void func2()
{
    TwoIntsClass * data;
    data = NULL;
    data = new TwoIntsClass;
    data->intOne = 1;
    data->intTwo = 2;
    printIntLine(data->intOne);
}

static void func3()
{
    TwoIntsClass * data;
    data = NULL;
    data = new TwoIntsClass;
    data->intOne = 1;
    data->intTwo = 2;
    delete data;
    ;
}

void func4()
{
    func2();
    func3();
}

}
