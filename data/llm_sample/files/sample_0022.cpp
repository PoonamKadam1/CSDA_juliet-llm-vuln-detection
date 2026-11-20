#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

static void func2()
{
    char * data;
    data = NULL;
    data = new char[100];
    memset(data, 'A', 100-1);
    data[100-1] = '\0';
    printLine(data);
}

static void func3()
{
    char * data;
    data = NULL;
    data = new char[100];
    memset(data, 'A', 100-1);
    data[100-1] = '\0';
    delete [] data;
    ;
}

void func4()
{
    func2();
    func3();
}

}
