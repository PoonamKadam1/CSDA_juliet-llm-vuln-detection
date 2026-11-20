#include "std_testcase.h"

void func1()
{
    short data;
    data = 0;
    fscanf (stdin, "%hd", &data);
    if(data > 0)
    {
        short result = data * 2;
        printIntLine(result);
    }
}
