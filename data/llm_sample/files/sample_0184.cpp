#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    char * data;
    data = NULL;
    data = new char[100];
    memset(data, 'A', 100-1);
    data[100-1] = '\0';
    delete [] data;
    printLine(data);
}

}
