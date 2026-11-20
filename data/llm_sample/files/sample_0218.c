#include "std_testcase.h"

void func1()
{
    unsigned int data;
    data = 0;
    fscanf (stdin, "%u", &data);
    {
        unsigned int result = data + 1;
        printUnsignedLine(result);
    }
}
