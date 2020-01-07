# include "libarray.h"

# include <stdio.h>

int main(void)
{
    // unsigned long   s = __UINT64_MAX__;
    // unsigned long   *ptr = &s;
    Array *aptr = ANew(unsigned long, 2UL);

    unsigned long   z = 0UL;
    unsigned long   n;

    do {
        printf("[%-19s]: %7zu | [%-3zu]: %-5lu -> ",
            aptr->tStr, aptr->size, aptr->length(aptr),
            ArrayGetDataAt(unsigned long, *aptr, z));

        n = z * 4.4 + 13.0 * 10.0;
        AAddElement(unsigned long, n, aptr);

        printf("[%-3zu]: %-5lu (%3zu)\n",
            aptr->length(aptr),
            ArrayGetDataAt(unsigned long, *aptr, z + 1), z + 1UL);
    } while (9 > ++z);

    printf("[%-19s]: %zu (%3zu)\n", aptr->tStr,
        aptr->length(aptr), aptr->size);
    ADelete(aptr, NULL);
}
