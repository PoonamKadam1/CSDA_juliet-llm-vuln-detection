#include "std_testcase.h"

void func1()
{
    short data;
    data = 0;
    if(GLOBAL_CONST_TRUE)
    {
        fscanf (stdin, "%hd", &data);
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            ++data;
            short result = data;
            printIntLine(result);
        }
    }
}
