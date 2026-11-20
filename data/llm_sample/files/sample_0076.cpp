#include "std_testcase.h"

namespace func1
{

void func2()
{
    int data;
    data = -1;
    if(GLOBAL_CONST_TRUE)
    {
        data = 10;
    }
    if(GLOBAL_CONST_TRUE)
    {
        {
            int i;
            int * buffer = new int[10];
            for (i = 0; i < 10; i++)
            {
                buffer[i] = 0;
            }
            if (data >= 0)
            {
                buffer[data] = 1;
                for(i = 0; i < 10; i++)
                {
                    printIntLine(buffer[i]);
                }
            }
            else
            {
                printLine("ERROR: Array index is negative.");
            }
            delete[] buffer;
        }
    }
}

}
