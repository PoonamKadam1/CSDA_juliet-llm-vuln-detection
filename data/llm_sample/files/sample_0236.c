#include "std_testcase.h"

void func1()
{
    int data;
    data = 0;
    data = INT_MAX;
    if(data > 0)
    {
        int result = data * 2;
        printIntLine(result);
    }
}
