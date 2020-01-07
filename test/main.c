# include "libinterface.h"

# include <stdio.h>

# define libi___(x, i) _Generic((x)0, float: i->id->f, default: i->id->l)

# define libi_(type, iptr) (type)iptr->id->libi___(type)

int main(void)
{
    Interface i;
    IInitialize(float, 2.0f, &i);

    Interface *iptr = INew(float, 2.4112f);

    size_t  z = ~0UL;
    float   n;

    printf("[%zu]: %f\n", iptr->n_el, InterfaceGetData(float, *iptr));
    while (9 > ++z) {
        n = z * 1.4f / 13.0f * 10.0f;
        IAddElement(float, n, iptr);
        printf("[%zu]: %f\n", iptr->n_el, iptr->id->f);
    }
    printf("[%s]: %zu (%zu)\n", iptr->tStr,
        iptr->length(iptr), iptr->size);
    IDelete(&i,   NULL);
    IDelete(iptr, NULL);
}
