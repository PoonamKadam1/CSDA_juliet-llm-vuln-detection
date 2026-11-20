#include "std_testcase.h"

void func1()
{
    short data;
    data = 0;
    data = (short)RAND32();
    {
        data++;
        short result = data;
        printIntLine(result);
    }
}
