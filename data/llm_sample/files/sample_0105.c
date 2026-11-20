#include "std_testcase.h"

static void func1()
{
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        {
            int *intPointer = NULL;
            if (intPointer == NULL)
            {
                printLine("pointer is NULL");
            }
        }
    }
}

static void func2()
{
    if(GLOBAL_CONST_TRUE)
    {
        {
            int *intPointer = NULL;
            if (intPointer == NULL)
            {
                printLine("pointer is NULL");
            }
        }
    }
}

void func3()
{
    func1();
    func2();
}
