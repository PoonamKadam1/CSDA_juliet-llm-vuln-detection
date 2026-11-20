#include "std_testcase.h"

#ifndef _WIN32
#include <wchar.h>
#endif

#define SRC_STRING L"AAAAAAAAAA"

static void func1()
{
    wchar_t * data;
    wchar_t func2[10];
    wchar_t func3[10+1];
    data = func3;
    data[0] = L'\0';
    {
        wchar_t source[10+1] = SRC_STRING;
        size_t i, sourceLen;
        sourceLen = wcslen(source);
        for (i = 0; i < sourceLen + 1; i++)
        {
            data[i] = source[i];
        }
        printWLine(data);
    }
}

void func4()
{
    func1();
}
