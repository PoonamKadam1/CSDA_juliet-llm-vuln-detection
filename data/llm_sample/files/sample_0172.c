#include "std_testcase.h"

void func1()
{
    int64_t data;
    data = 0LL;
    data = LLONG_MAX;
    {
        data++;
        int64_t result = data;
        printLongLongLine(result);
    }
}
