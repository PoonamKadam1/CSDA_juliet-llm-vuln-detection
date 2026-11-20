#include "std_testcase.h"

#include <wchar.h>

void func1()
{
    wchar_t * data;
    data = NULL;
    printWcharLine(data[0]);
}
