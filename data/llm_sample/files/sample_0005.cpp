#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    int64_t * data;
    data = NULL;
    data = new int64_t;
    *data = 5LL;
    delete data;
    printLongLongLine(*data);
}

}
