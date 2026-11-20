#include <inttypes.h>
#include "std_testcase.h"

void func1()
{
    int64_t data;
    data = 0LL;
    fscanf (stdin, "%" SCNd64, &data);
    {
        int64_t result = data + 1;
        printLongLongLine(result);
    }
}
