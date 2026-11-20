#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

static void func2()
{
    long * data;
    data = NULL;
    data = new long;
    *data = 5L;
    printLongLine(*data);
}

static void func3()
{
    long * data;
    data = NULL;
    data = new long;
    *data = 5L;
    delete data;
    ;
}

void func4()
{
    func2();
    func3();
}

}
