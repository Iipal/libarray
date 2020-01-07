# include "libinterface.h"

# include <stdio.h>

int main(void)
{
    Interface i;
    IInitialize(float, 2.0f, &i);

    Interface *iptr = INew(float, 2.4112);

    printf("%f\n", iptr->id->f);

    IDelete(&i,   NULL);
    IDelete(iptr, NULL);
}
