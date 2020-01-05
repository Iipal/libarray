# include "libinterface.h"

# include <stdio.h>

int main(void)
{
    Interface i;
    IInitialize(double, 2.0, &i);
    Interface *iptr = INew(int, 42);

    printf("'%-6s'[%zu]\n", i.tStr, i.size);
    printf("'%-6s'[%zu]\n", iptr->tStr, iptr->size);

    IDelete(iptr, NULL);
    IDelete(&i, NULL);
}
