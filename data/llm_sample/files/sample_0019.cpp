#include "std_testcase.h"

#ifndef _WIN32
#include <wchar.h>
#endif

#define SRC_STRING "AAAAAAAAAA"

namespace func1
{

void func2()
{
    char * data;
    data = NULL;
    data = new char[10];
    {
        char source[10+1] = SRC_STRING;
        memcpy(data, source, (strlen(source) + 1) * sizeof(char));
        printLine(data);
        delete [] data;
    }
}

}
