#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    TwoIntsClass * data;
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = new TwoIntsClass[100];
        {
            size_t i;
            for(i = 0; i < 100; i++)
            {
                data[i].intOne = 1;
                data[i].intTwo = 2;
            }
        }
        delete [] data;
    }
    if(GLOBAL_CONST_TRUE)
    {
        printIntLine(data[0].intOne);
    }
}

}
