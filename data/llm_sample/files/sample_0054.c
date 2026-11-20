#include "std_testcase.h"

#include <wchar.h>

static void func1()
{
    char * data;
    data = NULL;
    data = (char *)malloc(100*sizeof(char));
    if (data == NULL) {exit(-1);}
    data[0] = '\0';
    {
        char source[100];
        memset(source, 'C', 100-1);
        source[100-1] = '\0';
        memcpy(data, source, 100*sizeof(char));
        data[100-1] = '\0';
        printLine(data);
        free(data);
    }
}

void func2()
{
    func1();
}
