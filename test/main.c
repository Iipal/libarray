#include "libinterface.h"
# define LIBI_INTERNAL
# include "libi_internal.h"
# undef LIBI_INTERNAL
# include <stdio.h>

int main(void)
{
    // Interface a = libi_create_interface("int", -42, libi_get_type(int))

    printf("%d\n", _Generic(char,
        char: e_type_c, unsigned char: e_type_uc,
        short: e_type_s, unsigned short: e_type_us,
        int: e_type_i, unsigned int: e_type_ui,
        long: e_type_l, unsigned long: e_type_ul,
        long long: e_type_ll, unsigned long long: e_type_ull,
        double: e_type_d, long double: e_type_ld,
        float: e_type_f, default: e_type_ptr));
}
