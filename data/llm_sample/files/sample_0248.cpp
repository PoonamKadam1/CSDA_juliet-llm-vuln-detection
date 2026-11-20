#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

static void func2()
{
    int64_t * data;
    data = NULL;
    data = new int64_t;
    *data = 5LL;
    printLongLongLine(*data);
}

static void func3()
{
    int64_t * data;
    data = NULL;
    data = new int64_t;
    *data = 5LL;
    delete data;
    ;
}

void func4()
{
    func2();
    func3();
}

}
