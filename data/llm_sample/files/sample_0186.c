#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    char * data;
    char dataBuffer[100];
    data = dataBuffer;
    memset(data, 'A', 50-1);
    data[50-1] = '\0';
    {
        char dest[50] = "";
        strcpy(dest, data);
        printLine(data);
    }
}

void func2()
{
    func1();
}
