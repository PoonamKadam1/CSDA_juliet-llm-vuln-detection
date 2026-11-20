#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    int * data;
    data = NULL;
    data = new int;
    *data = 5;
    delete data;
    printIntLine(*data);
}

}
