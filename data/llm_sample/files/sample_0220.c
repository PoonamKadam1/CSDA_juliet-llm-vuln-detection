#include "std_testcase.h"

void func1()
{
    unsigned int data;
    data = 0;
    if(GLOBAL_CONST_TRUE)
    {
        fscanf (stdin, "%u", &data);
    }
    if(GLOBAL_CONST_TRUE)
    {
        if(data > 0)
        {
            unsigned int result = data * 2;
            printUnsignedLine(result);
        }
    }
}
