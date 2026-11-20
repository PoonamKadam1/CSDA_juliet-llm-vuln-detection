#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

static void func2()
{
    twoIntsStruct * data;
    data = NULL;
    data = new twoIntsStruct;
    data->intOne = 1;
    data->intTwo = 2;
    printStructLine(data);
}

static void func3()
{
    twoIntsStruct * data;
    data = NULL;
    data = new twoIntsStruct;
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
