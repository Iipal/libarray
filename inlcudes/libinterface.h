#ifndef LIBINTERFACE_H
# define LIBINTERFACE_H

# define _GNU_SOURCE

# define LIBI_INTERNAL_TYPES
# include "libi_types.h"
# undef LIBI_INTERNAL_TYPES

# define _GNU_SOURCE

# include <stdlib.h>
# include <stddef.h>
# include <assert.h>
# include <string.h>
# include <strings.h>
# include <stdbool.h>
# include <err.h>

static void
libi_validate_type(const char *restrict __tStr, InterfaceDataType __idt)
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
    if (!!*__valid_types[__idt] && !!strcmp(__tStr, __valid_types[__idt]))
        errx(EXIT_FAILURE, "libinterface: passing invalid data: '%s' to '%s'",
            __valid_types[__idt], __tStr);
}

# define IInitialize(type, data, dst_ptr) \
    libi_initialize_fn((InterfaceData)data, \
        libi_data_type_generic(data), #type, sizeof(type), dst_ptr)

static inline void
libi_initialize_fn(InterfaceData __id,
                   InterfaceDataType __idt,
                   const char *restrict __tStr,
                   const size_t __size,
                   Interface *restrict __dst)
{

    assert(!(IDTPtr == __idt && NULL == __id.ptr));
    libi_validate_type(__tStr, __idt);
    *__dst = (Interface) {
        libi_dup_static_id(__id), strdup(__tStr), __size, __idt, false
    };
}

# define INew(type, data) \
    libi_fn_inew((InterfaceData)data, \
        libi_data_type_generic(data), #type, sizeof(type))

static inline Interface
*libi_fn_inew(InterfaceData __id,
              InterfaceDataType __idt,
              const char *restrict __tStr,
              const size_t __size)
{
    Interface   *__out_ptr;

    assert((__out_ptr = calloc(1UL, sizeof(*__out_ptr))));
    libi_initialize_fn(__id, __idt, __tStr, __size, __out_ptr);
    __out_ptr->__is_allocated = true;
    return __out_ptr;
}

static inline void
IDelete(Interface *restrict __i, void (*__callback_freeing_ptr)(void*,size_t)) {
    if (!!__i) {
        if (!!__i->id) {
            if (IDTPtr == __i->idt && !!__callback_freeing_ptr)
                __callback_freeing_ptr(__i->id->ptr, __i->size);
            free(__i->id);
        }
        free(__i->tStr);
        if (!!__i->__is_allocated)
            free(__i);
    }
}

#endif /* LIBINTERFACE_H */
