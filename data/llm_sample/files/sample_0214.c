#include "std_testcase.h"

void func1()
{
    int64_t data;
    data = 0LL;
    if(GLOBAL_CONST_TRUE)
    {
        data = LLONG_MAX;
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            int64_t result = data + 1;
            printLongLongLine(result);
        }
    }
}
