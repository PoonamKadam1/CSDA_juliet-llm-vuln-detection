#include "std_testcase.h"

#ifndef _WIN32
#include <wchar.h>
#endif

#define SRC_STRING "AAAAAAAAAA"

static void func1()
{
    char * data;
    char func2[10];
    char func3[10+1];
    if(GLOBAL_CONST_FALSE)
    {
        printLine("Benign, fixed string");
    }
    else
    {
        data = func3;
        data[0] = '\0';
    }
    {
        char source[10+1] = SRC_STRING;
        memcpy(data, source, (strlen(source) + 1) * sizeof(char));
        printLine(data);
    }
}

static void func4()
{
    char * data;
    char func2[10];
    char func3[10+1];
    if(GLOBAL_CONST_TRUE)
    {
        data = func3;
        data[0] = '\0';
    }
    {
        char source[10+1] = SRC_STRING;
        memcpy(data, source, (strlen(source) + 1) * sizeof(char));
        printLine(data);
    }
}

void func5()
{
    func1();
    func4();
}
