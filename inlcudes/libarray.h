#ifndef LIBARRAY_H
# define LIBARRAY_H

# define _GNU_SOURCE

# define LIBA_INTERNAL
# include "liba_internal.h"
# undef LIBA_INTERNAL

# undef AInitialize
# define AInitialize(type, data, dst_ptr) \
    liba_initialize_fn((__internalData)(data), \
        liba_get_data_type(data), #type, sizeof(type), dst_ptr)

# undef AAddElement
# define AAddElement(type, data, dst_ptr) \
    liba_initialize_fn((__internalData)(data), \
        (dst_ptr)->_internal._dt, #type, sizeof(type), dst_ptr)

# undef ANew
# define ANew(type, data) \
    liba_anew_fn((__internalData)(data), \
        liba_get_data_type(data), #type, sizeof(type))

# undef ArrayGetElementAt
# define ArrayGetElementAt(type, a, at) ((type)_Generic((type)0,                                        \
    char:               (a)._internal._d[(at)].c,   char*:               (a)._internal._d[(at)].cptr,   \
    unsigned char:      (a)._internal._d[(at)].uc,  unsigned char*:      (a)._internal._d[(at)].ucptr,  \
    short:              (a)._internal._d[(at)].s,   short*:              (a)._internal._d[(at)].sptr,   \
    unsigned short:     (a)._internal._d[(at)].us,  unsigned short*:     (a)._internal._d[(at)].usptr,  \
    int:                (a)._internal._d[(at)].i,   int*:                (a)._internal._d[(at)].iptr,   \
    unsigned int:       (a)._internal._d[(at)].ui,  unsigned int*:       (a)._internal._d[(at)].uiptr,  \
    long:               (a)._internal._d[(at)].l,   long*:               (a)._internal._d[(at)].lptr,   \
    unsigned long:      (a)._internal._d[(at)].ul,  unsigned long*:      (a)._internal._d[(at)].ulptr,  \
    long long:          (a)._internal._d[(at)].ll,  long long*:          (a)._internal._d[(at)].llptr,  \
    unsigned long long: (a)._internal._d[(at)].ull, unsigned long long*: (a)._internal._d[(at)].ullptr, \
    double:             (a)._internal._d[(at)].d,   double*:             (a)._internal._d[(at)].dptr,   \
    long double:        (a)._internal._d[(at)].ld,  long double*:        (a)._internal._d[(at)].ldptr,  \
    float:              (a)._internal._d[(at)].f,   float*:              (a)._internal._d[(at)].fptr,   \
    default:            (a)._internal._d[(at)].ptr))

# undef ArrayGetDataTypeName
# define ArrayGetDataTypeName(a) ((a)._internal._tStr)

static inline void ADelete(Array *restrict _a,
    void (*_callback_freeing_ptr)(void*,size_t))
        __attribute__((alias("liba_adelete_fn")));

#endif /* LIBARRAY_H */
