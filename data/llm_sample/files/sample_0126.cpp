#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    wchar_t * data;
    data = new wchar_t[100];
    if(GLOBAL_CONST_TRUE)
    {
        wmemset(data, L'A', 100-1);
        data[100-1] = L'\0';
    }
    {
        wchar_t dest[50] = L"";
        wcsncat(dest, data, wcslen(data));
        dest[50-1] = L'\0';
        printWLine(data);
        delete [] data;
    }
}

}
