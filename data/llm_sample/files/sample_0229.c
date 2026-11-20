#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    char * data;
    char * func2 = (char *)ALLOCA(50*sizeof(char));
    char * func3 = (char *)ALLOCA(100*sizeof(char));
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
        char source[100];
        memset(source, 'C', 100-1);
        source[100-1] = '\0';
        strncat(data, source, 100);
        printLine(data);
    }
}

static void func4()
{
    char * data;
    char * func2 = (char *)ALLOCA(50*sizeof(char));
    char * func3 = (char *)ALLOCA(100*sizeof(char));
    if(GLOBAL_CONST_TRUE)
    {
        data = func3;
        data[0] = '\0';
    }
    {
        char source[100];
        memset(source, 'C', 100-1);
        source[100-1] = '\0';
        strncat(data, source, 100);
        printLine(data);
    }
}

void func5()
{
    func1();
    func4();
}
