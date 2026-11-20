#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    wchar_t * data;
    wchar_t * dataBuffer = (wchar_t *)ALLOCA(100*sizeof(wchar_t));
    data = dataBuffer;
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        wmemset(data, L'A', 50-1);
        data[50-1] = L'\0';
    }
    {
        wchar_t dest[50] = L"";
        wcscpy(dest, data);
        printWLine(data);
    }
}

static void func2()
{
    wchar_t * data;
    wchar_t * dataBuffer = (wchar_t *)ALLOCA(100*sizeof(wchar_t));
    data = dataBuffer;
    if(GLOBAL_CONST_TRUE)
    {
        wmemset(data, L'A', 50-1);
        data[50-1] = L'\0';
    }
    {
        wchar_t dest[50] = L"";
        wcscpy(dest, data);
        printWLine(data);
    }
}

void func3()
{
    func1();
    func2();
}
