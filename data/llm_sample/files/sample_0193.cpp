#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    TwoIntsClass * data;
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = new TwoIntsClass;
        data->intOne = 1;
        data->intTwo = 2;
        delete data;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printIntLine(data->intOne);
    }
}

}
