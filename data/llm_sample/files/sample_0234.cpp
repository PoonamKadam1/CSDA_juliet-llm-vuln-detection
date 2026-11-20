#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    TwoIntsClass * data;
    data = NULL;
    data = new TwoIntsClass;
    data->intOne = 1;
    data->intTwo = 2;
    delete data;
    printIntLine(data->intOne);
}

}
