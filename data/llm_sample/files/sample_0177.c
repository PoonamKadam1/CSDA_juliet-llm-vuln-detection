#include "std_testcase.h"

void func1()
{
    twoIntsStruct * data;
    twoIntsStruct * func2 = (twoIntsStruct *)ALLOCA(50*sizeof(twoIntsStruct));
    twoIntsStruct * func3 = (twoIntsStruct *)ALLOCA(100*sizeof(twoIntsStruct));
    data = func2;
    {
        twoIntsStruct source[100];
        {
            size_t i;
            for (i = 0; i < 100; i++)
            {
                source[i].intOne = 0;
                source[i].intTwo = 0;
            }
        }
        memcpy(data, source, 100*sizeof(twoIntsStruct));
        printStructLine(&data[0]);
    }
}
