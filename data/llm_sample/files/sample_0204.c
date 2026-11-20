#include "std_testcase.h"

void func1()
{
    if(GLOBAL_CONST_TRUE)
    {
        {
            twoIntsStruct *twoIntsStructPointer = NULL;
            if ((twoIntsStructPointer != NULL) & (twoIntsStructPointer->intOne == 5))
            {
                printLine("intOne == 5");
            }
        }
    }
}
