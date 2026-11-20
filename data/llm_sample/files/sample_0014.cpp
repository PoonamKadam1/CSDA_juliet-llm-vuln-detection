#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    long * data;
    data = NULL;
    data = new long;
    *data = 5L;
    delete data;
    printLongLine(*data);
}

}
