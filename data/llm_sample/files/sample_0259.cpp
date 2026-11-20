#include "std_testcase.h"

namespace func1
{

void func2()
{
    TwoIntsClass * data;
    data = NULL;
    printIntLine(data->intOne);
    delete data;
}

}
