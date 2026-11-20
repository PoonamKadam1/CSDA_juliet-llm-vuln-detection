#include "std_testcase.h"

#include <wchar.h>

namespace func1
{

void func2()
{
    char * data;
    data = new char[100];
    if(GLOBAL_CONST_TRUE)
    {
        memset(data, 'A', 100-1);
        data[100-1] = '\0';
    }
    {
        char dest[50] = "";
        strcpy(dest, data);
        printLine(data);
        delete [] data;
    }
}

}
