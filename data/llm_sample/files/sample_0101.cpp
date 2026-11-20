#include "std_testcase.h"

namespace func1
{

void func2()
{
    TwoIntsClass * data;
    if(GLOBAL_CONST_TRUE)
    {
        data = NULL;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printIntLine(data->intOne);
        delete data;
    }
}

}
