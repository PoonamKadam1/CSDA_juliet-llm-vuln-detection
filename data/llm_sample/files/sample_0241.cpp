#include "std_testcase.h"

#ifndef _WIN32
#include <wchar.h>
#endif

#define SRC_STRING L"AAAAAAAAAA"

namespace func1
{

void func2()
{
    wchar_t * data;
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = new wchar_t[10];
    }
    {
        wchar_t source[10+1] = SRC_STRING;
        memcpy(data, source, (wcslen(source) + 1) * sizeof(wchar_t));
        printWLine(data);
        delete [] data;
    }
}

}
