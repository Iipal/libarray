#ifndef LIBARRAY_H
# define LIBARRAY_H

# define _GNU_SOURCE

# define LIBA_INTERNAL
# include "liba_types.h"
# undef LIBA_INTERNAL

# include <stdlib.h>
# include <stddef.h>
# include <assert.h>
# include <string.h>
# include <strings.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <err.h>

static void
liba_validate_type(const char *restrict __tStr, ArrayDataType __adt)
{
    static char *__valid_types[27] = {
        "char",               "char*",
        "unsigned char",      "unsigned char*",
        "short",              "short*",
        "unsigned short",     "unsigned short*",
        "int",                "int*",
        "unsigned int",       "unsigned int*",
        "long",               "long*",
        "unsigned long",      "unsigned long*",
        "long long",          "long long*",
        "unsigned long long", "unsigned long long*",
        "double",             "double*",
        "long double",        "long double*",
        "float",              "float*",
        ""
    };

    // If passing the pointer data type it's don't needed to processing errno
    if (!!*__valid_types[__adt] && !!strcmp(__tStr, __valid_types[__adt])) {
        warnx((!isatty(fileno(stdout))
            ? "libarray: passing invalid data: '%s' to '%s'"
            : "\e[35mlibarray\e[39m: passing invalid data: '\e[31m%s\e[39m' to '\e[35m%s\e[39m'"),
            __valid_types[__adt], __tStr);
    }
}

# define AInitialize(type, data, dst_ptr) \
    liba_initialize_fn((ArrayData)(data), \
        liba_get_data_type(data), #type, sizeof(type), dst_ptr)

static inline void
liba_initialize_fn(const ArrayData __ad,
                   const ArrayDataType __adt,
                   const char *restrict __tStr,
                   const size_t __size,
                   Array *restrict __dst)
{

    assert(!(ADT_Ptr == __adt && NULL == __ad.ptr));
    liba_validate_type(__tStr, __adt);
    __dst->ad = realloc(__dst->ad, sizeof(ArrayData) * (__dst->n_el + 1UL));
    memcpy(__dst->ad + __dst->n_el, &__ad, sizeof(ArrayData));
    if (!__dst->length)
        __dst->length = liba_length;
    if (!__dst->tStr)
        __dst->tStr = strdup(__tStr);
    __dst->adt = __adt;
    __dst->size = ++__dst->n_el * __size;
}

# define AAddElement(type, data, dst_ptr) \
    liba_aaddel_fn((ArrayData)(data), #type, sizeof(type), dst_ptr)

static inline void
liba_aaddel_fn(const ArrayData __ad,
               const char *restrict __tStr,
               const size_t __size,
               Array *restrict __dst)
{
    liba_initialize_fn(__ad, __dst->adt, __tStr, __size, __dst);
}

# define ANew(type, data) \
    liba_fn_inew((ArrayData)data, \
        liba_get_data_type(data), #type, sizeof(type))

static inline Array*
liba_fn_inew(ArrayData __ad,
             ArrayDataType __adt,
             const char *restrict __tStr,
             const size_t __size)
{
    Array   *__out_ptr;

    assert((__out_ptr = calloc(1UL, sizeof(*__out_ptr))));
    liba_initialize_fn(__ad, __adt, __tStr, __size, __out_ptr);
    __out_ptr->__is_allocated = true;
    return __out_ptr;
}

static inline void
ADelete(Array *restrict __a, void (*__callback_freeing_ptr)(void*,size_t)) {
    if (!!__a) {
        if (!!__a->ad) {
            if (ADT_Ptr == __a->adt && !!__callback_freeing_ptr)
                __callback_freeing_ptr(__a->ad->ptr, __a->size);
            free(__a->ad);
        }
        free(__a->tStr);
        if (!!__a->__is_allocated)
            free(__a);
    }
}

#endif /* LIBARRAY_H */
