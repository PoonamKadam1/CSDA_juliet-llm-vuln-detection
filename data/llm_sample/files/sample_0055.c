#include "std_testcase.h"

void func1()
{
    {
        int *intPointer = NULL;
        if (intPointer == NULL)
        {
            printIntLine(*intPointer);
        }
    }
}
