#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

static void func2()
{
    int * data;
    data = NULL;
    data = new int;
    *data = 5;
    printIntLine(*data);
}

static void func3()
{
    int * data;
    data = NULL;
    data = new int;
    *data = 5;
    delete data;
    ;
}

void func4()
{
    func2();
    func3();
}

}
