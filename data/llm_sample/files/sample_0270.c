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
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = func3;
        data[0] = L'\0';
    }
    {
        wchar_t source[10+1] = SRC_STRING;
        wcscpy(data, source);
        printWLine(data);
    }
}

static void func4()
{
    wchar_t * data;
    wchar_t func2[10];
    wchar_t func3[10+1];
    if(GLOBAL_CONST_TRUE)
    {
        data = func3;
        data[0] = L'\0';
    }
    {
        wchar_t source[10+1] = SRC_STRING;
        wcscpy(data, source);
        printWLine(data);
    }
}

void func5()
{
    func1();
    func4();
}
