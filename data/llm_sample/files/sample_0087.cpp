#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    twoIntsStruct * data;
    data = NULL;
    data = new twoIntsStruct;
    data->intOne = 1;
    data->intTwo = 2;
    delete data;
    printStructLine(data);
}

}
