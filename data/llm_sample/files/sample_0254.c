#include "std_testcase.h"

void func1()
{
    if(GLOBAL_CONST_TRUE)
    {
        {
            int *intPointer = NULL;
            if (intPointer == NULL)
            {
                printIntLine(*intPointer);
            }
        }
    }
}
