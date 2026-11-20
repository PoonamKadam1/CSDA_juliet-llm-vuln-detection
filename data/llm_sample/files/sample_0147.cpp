#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

static void func2()
{
    wchar_t * data;
    data = NULL;
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = new wchar_t[100];
        data[0] = L'\0';
    }
    {
        size_t i;
        wchar_t source[100];
        wmemset(source, L'C', 100-1);
        source[100-1] = L'\0';
        for (i = 0; i < 100; i++)
        {
            data[i] = source[i];
        }
        data[100-1] = L'\0';
        printWLine(data);
        delete [] data;
    }
}

static void func3()
{
    wchar_t * data;
    data = NULL;
    if(GLOBAL_CONST_TRUE)
    {
        data = new wchar_t[100];
        data[0] = L'\0';
    }
    {
        size_t i;
        wchar_t source[100];
        wmemset(source, L'C', 100-1);
        source[100-1] = L'\0';
        for (i = 0; i < 100; i++)
        {
            data[i] = source[i];
        }
        data[100-1] = L'\0';
        printWLine(data);
        delete [] data;
    }
}

void func4()
{
    func2();
    func3();
}

}
