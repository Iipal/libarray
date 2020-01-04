#ifndef LIBI_INTERNAL_H
# define LIBI_INTERNAL_H

# ifndef LIBI_INTERNAL
#  error "include only libinterface.h"
# endif

# include "libi_generic_functions.h"

# include <stdlib.h>
# include <assert.h>

# ifndef S_INTERFACE
#  define S_INTERFACE

typedef size_t (*libi_fptr_length)(void *restrict);

struct s_interface {
    void *restrict      data;
    libi_fptr_length    length;
} __attribute__((aligned(__BIGGEST_ALIGNMENT__)));

typedef struct s_interface* Interface;

# endif /* S_INTERFACE */

typedef enum   e_type_generic {
    e_type_c,  e_type_uc,
    e_type_s,  e_type_us,
    e_type_i,  e_type_ui,
    e_type_l,  e_type_ul,
    e_type_ll, e_type_ull,
    e_type_d,  e_type_ld,
    e_type_f,
    e_type_ptr
} __attribute__((packed)) InterfaceType;

# define libi_get_type(x) _Generic((x),                    \
    char:      e_type_c,  unsigned char:      e_type_uc,  \
    short:     e_type_s,  unsigned short:     e_type_us,  \
    int:       e_type_i,  unsigned int:       e_type_ui,  \
    long:      e_type_l,  unsigned long:      e_type_ul,  \
    long long: e_type_ll, unsigned long long: e_type_ull, \
    double:    e_type_d,  long double:        e_type_ld,  \
    float:     e_type_f,                                  \
    default:   e_type_ptr)

# define create_interface(type, data) \
    libi_create_interface(#type, data, libi_get_type(type))

static libi_fptr_length
libi_get_length_fn(InterfaceType itype)
{
    static libi_fptr_length fns[16] = {
        libi_c_length, libi_uc_length,
        libi_s_length, libi_us_length,
        libi_i_length, libi_ui_length,
        libi_l_length, libi_ul_length,
        libi_ll_length, libi_ul_length,
        libi_d_length, libi_ld_length,
        libi_f_length,
        libi_ptr_length,
        NULL, NULL
    };

    return (fns[itype]);
}

static Interface
libi_create_interface(char *stype, void *data, InterfaceType itype)
{
    struct s_interface  *new;

    assert(data);
    assert((new = aligned_alloc(sizeof(*new), sizeof(*new))));
    *new = (struct s_interface) {
        .data = data,
        .length = libi_get_length_fn(itype)
    };
    return new;
}

#endif /* LIBINTERFACE_INTERNAL_H */
