#include "std_testcase.h"

#ifndef _WIN32
#include <wchar.h>
#endif

#define SRC_STRING "AAAAAAAAAA"

static void func1()
{
    char * data;
    char * func2 = (char *)ALLOCA((10)*sizeof(char));
    char * func3 = (char *)ALLOCA((10+1)*sizeof(char));
    data = func3;
    data[0] = '\0';
    {
        char source[10+1] = SRC_STRING;
        size_t i, sourceLen;
        sourceLen = strlen(source);
        for (i = 0; i < sourceLen + 1; i++)
        {
            data[i] = source[i];
        }
        printLine(data);
    }
}

void func4()
{
    func1();
}
