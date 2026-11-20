#include "std_testcase.h"

#include <wchar.h>

void func1()
{
    wchar_t * data;
    wchar_t func2[50];
    wchar_t func3[100];
    if(GLOBAL_CONST_TRUE)
    {
        data = func2;
        data[0] = L'\0';
    }
    {
        wchar_t source[100];
        wmemset(source, L'C', 100-1);
        source[100-1] = L'\0';
        memcpy(data, source, 100*sizeof(wchar_t));
        data[100-1] = L'\0';
        printWLine(data);
    }
}
