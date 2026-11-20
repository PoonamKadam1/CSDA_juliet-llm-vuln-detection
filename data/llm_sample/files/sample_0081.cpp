#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

static void func2()
{
    wchar_t * data;
    data = NULL;
    data = new wchar_t[100];
    wmemset(data, L'A', 100-1);
    data[100-1] = L'\0';
    printWLine(data);
}

static void func3()
{
    wchar_t * data;
    data = NULL;
    data = new wchar_t[100];
    wmemset(data, L'A', 100-1);
    data[100-1] = L'\0';
    delete [] data;
    ;
}

void func4()
{
    func2();
    func3();
}

}
