#include "std_testcase.h"

void func1()
{
    int64_t data;
    data = 0LL;
    if(GLOBAL_CONST_TRUE)
    {
        data = (int64_t)RAND64();
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            ++data;
            int64_t result = data;
            printLongLongLine(result);
        }
    }
}
