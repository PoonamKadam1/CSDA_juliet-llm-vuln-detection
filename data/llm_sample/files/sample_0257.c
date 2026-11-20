#include "std_testcase.h"

static void func1()
{
    {
        twoIntsStruct *twoIntsStructPointer = NULL;
        if ((twoIntsStructPointer != NULL) && (twoIntsStructPointer->intOne == 5))
        {
            printLine("intOne == 5");
        }
    }
}

void func2()
{
    func1();
}
