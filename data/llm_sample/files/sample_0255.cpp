#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    int * data;
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = new int;
        *data = 5;
        delete data;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printIntLine(*data);
    }
}

}
