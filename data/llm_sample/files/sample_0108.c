#include "std_testcase.h"

#include <wchar.h>

#ifdef _WIN32
#define SNPRINTF _snprintf
#else
#define SNPRINTF snprintf
#endif

void func1()
{
    char * data;
    char func2[50];
    char func3[100];
    data = func2;
    data[0] = '\0';
    {
        char source[100];
        memset(source, 'C', 100-1);
        source[100-1] = '\0';
        SNPRINTF(data, 100, "%s", source);
        printLine(data);
    }
}
