#include "std_testcase.h"

static void func1()
{
    {
        int *intPointer = NULL;
        if (intPointer == NULL)
        {
            printLine("pointer is NULL");
        }
    }
}

void func2()
{
    func1();
}
