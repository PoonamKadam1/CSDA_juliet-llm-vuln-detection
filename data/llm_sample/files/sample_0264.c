#include "std_testcase.h"

#ifndef _WIN32
#include <wchar.h>
#endif

#define SRC_STRING "AAAAAAAAAA"

void func1()
{
    char * data;
    char func2[10];
    char func3[10+1];
    data = func2;
    data[0] = '\0';
    {
        char source[10+1] = SRC_STRING;
        memmove(data, source, (strlen(source) + 1) * sizeof(char));
        printLine(data);
    }
}
