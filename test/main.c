# include "libarray.h"

# include <stdio.h>

// void    test1(bool is_print_data)
// {
//     if (is_print_data) {
//         printf("\n\ttest with default C data types and adding new elements:\n\n");
//     }
//     Array *aptr = ANew(unsigned long, 2UL);

//     unsigned long   z = 0UL;
//     unsigned long   n;

//     do {
//         if (is_print_data)
//             printf("[%-19s]: %7zu | [%-3zu]: %-5lu -> ",
//                 ArrayGetDataTypeName(*aptr), aptr->size(aptr), aptr->length(aptr),
//                 ArrayGetElementAt(unsigned long, *aptr, z));

//         n = z * 4.4 + 13.0 * 10.0;
//         AAddElement(unsigned long, n, aptr);

//         if (is_print_data)
//             printf("[%-3zu]: %-5lu (%3zu)\n", aptr->length(aptr),
//                 ArrayGetElementAt(unsigned long, *aptr, z + 1), z + 1UL);
//     } while (9 > ++z);
//     if (is_print_data)
//         printf("[%-19s]: %zu (%3zu)\n",
//             ArrayGetDataTypeName(*aptr),
//             aptr->length(aptr),
//             aptr->size(aptr));
//     ADelete(aptr, NULL);
// }

void    test2(bool is_print_data)
{
    if (is_print_data) {
        printf("\n\ttest with pointers:\n\n");
    }
    long     d = 10L;
    Array   *aptr = ANew(int*, &d);

    if (is_print_data) {
        printf("[%-19s]:\n"
               "src ptr     : %p (%3ld)\n"
               "ptr in Array: %p (%3d)\n",
            ArrayGetDataTypeName(*aptr),
            &d, d,
            ArrayGetElementAt(int*, *aptr, 0),
            *ArrayGetElementAt(int*, *aptr, 0));
    }

    ADelete(aptr, NULL);
}

int main(void)
{
    // test1(true);
    test2(true);
}
