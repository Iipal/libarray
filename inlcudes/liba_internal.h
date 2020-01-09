#ifndef LIBA_INTERNAL_H
# define LIBA_INTERNAL_H

# ifndef LIBA_INTERNAL
# error "inlcude only libinterface.h"
# endif

# include <stdbool.h>
# include <strings.h>
# include <stddef.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <err.h>

# ifndef E_DATA_TYPE
#  define E_DATA_TYPE

typedef enum e_data_type __internalDataType;

enum    e_data_type
{
    __TypeC,   __TypeCPtr,   // char               | char*
    __TypeUC,  __TypeUCPtr,  // unsigned char      | unsigned char*
    __TypeS,   __TypeSPtr,   // short              | short*
    __TypeUS,  __TypeUSPtr,  // unsigned short     | unsigned short*
    __TypeI,   __TypeIPtr,   // int                | int*
    __TypeUI,  __TypeUIPtr,  // unsigned int       | unsigned int*
    __TypeL,   __TypeLPtr,   // long               | long*
    __TypeUL,  __TypeULPtr,  // unsigned long      | unsigned long*
    __TypeLL,  __TypeLLPtr,  // long long          | long long*
    __TypeULL, __TypeULLPtr, // unsigned long long | unsigned long long*
    __TypeD,   __TypeDPtr,   // double             | double*
    __TypeLD,  __TypeLDPtr,  // long double        | long double*
    __TypeF,   __TypeFPtr,   // float              | float*
    __TypePtr                // void* or anything else
} __attribute__((packed));

# undef liba_get_data_type
# define liba_get_data_type(x) _Generic((x) + 0,                      \
    char:               __TypeC,   char*:               __TypeCPtr,   \
    unsigned char:      __TypeUC,  unsigned char*:      __TypeUCPtr,  \
    short:              __TypeS,   short*:              __TypeSPtr,   \
    unsigned short:     __TypeUS,  unsigned short*:     __TypeUSPtr,  \
    int:                __TypeI,   int*:                __TypeIPtr,   \
    unsigned int:       __TypeUI,  unsigned int*:       __TypeUIPtr,  \
    long:               __TypeL,   long*:               __TypeLPtr,   \
    unsigned long:      __TypeUL,  unsigned long*:      __TypeULPtr,  \
    long long:          __TypeLL,  long long*:          __TypeLLPtr,  \
    unsigned long long: __TypeULL, unsigned long long*: __TypeULLPtr, \
    double:             __TypeD,   double*:             __TypeDPtr,   \
    long double:        __TypeLD,  long double*:        __TypeLDPtr,  \
    float:              __TypeF,   float*:              __TypeFPtr,   \
    default:            __TypePtr)

static void
liba_validate_type(const char *restrict _tStr, __internalDataType _dt)
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
    if (!!*__valid_types[_dt] && !!strcmp(_tStr, __valid_types[_dt])) {
        warnx((!isatty(fileno(stdout))
            ? "libarray: passing invalid data: '%s' to '%s'"
            : "\e[35mlibarray\e[39m: passing invalid data: '\e[31m%s\e[39m' to '\e[35m%s\e[39m'"),
            __valid_types[_dt], _tStr);
    }
}

# endif /* E_DATA_TYPE */

# ifndef U_DATA
#  define U_DATA

typedef union u_data __internalData;

union u_data
{
    char                c;   char                *cptr;
    unsigned char       uc;  unsigned char       *ucptr;
    short               s;   short               *sptr;
    unsigned short      us;  unsigned short      *usptr;
    int                 i;   int                 *iptr;
    unsigned int        ui;  unsigned int        *uiptr;
    long                l;   long                *lptr;
    unsigned long       ul;  unsigned long       *ulptr;
    long long           ll;  long long           *llptr;
    unsigned long long  ull; unsigned long long  *ullptr;
    double              d;   double              *dptr;
    long double         ld;  long double         *ldptr;
    float               f;   float               *fptr;
    void                *ptr;
};

# endif /* U_DATA */

# ifndef S_INTERNAL_ARRAY
#  define S_INTERNAL_ARRAY

typedef struct s_internal_array _internalArray;

struct s_internal_array
{
    __internalData *restrict    _d;
    char *restrict              _tStr;
    size_t                      _tSize;
    size_t                      _nEl;
    __internalDataType          _dt;
    bool                        _is_allocated;
    bool                        _is_initialized;
    char                        __dummy[5] __attribute__((unused));
} __attribute__((aligned(__BIGGEST_ALIGNMENT__)));

# endif /* S_INTERNAL_ARRAY */

# ifndef S_ARRAY
#  define S_ARRAY

typedef struct s_array Array;

typedef size_t (*liba_fnptr_length)(const Array *restrict);
typedef size_t (*liba_fnptr_size)(const Array *restrict);

struct s_array
{
    _internalArray     _internal;
    liba_fnptr_length   length;
    liba_fnptr_size     size;
} __attribute__((aligned(__BIGGEST_ALIGNMENT__)));

static size_t
liba_length_fn(const Array *restrict a)
{
    sizeof(__)
    return a->_internal._nEl;
}

static size_t
liba_size_fn(const Array *restrict a)
{
    return a->_internal._nEl * a->_internal._tSize;
}

static inline void
liba_initialize_fn(const __internalData _d,
                   const __internalDataType _dt,
                   const char *restrict _tStr,
                   const size_t _size,
                   Array *restrict _dst)
{
    _internalArray *restrict __iptr = &_dst->_internal;

    assert(!(__TypePtr == _dt && NULL == _d.ptr));
    liba_validate_type(_tStr, _dt);
    __iptr->_d = realloc(__iptr->_d,
        sizeof(__internalData) * (__iptr->_nEl + 1UL));
    *(__iptr->_d + __iptr->_nEl) = _d;
    if (!__iptr->_is_initialized) {
        _dst->size = liba_size_fn;
        _dst->length = liba_length_fn;
        __iptr->_dt = _dt;
        __iptr->_tSize = _size;
        __iptr->_tStr = strdup(_tStr);
        __iptr->_is_initialized = true;
    }
    __iptr->_nEl++;
}

static inline Array*
liba_anew_fn(__internalData _d,
             __internalDataType _dt,
             const char *restrict _tStr,
             const size_t _size)
{
    Array   *_out_ptr;

    assert((_out_ptr = calloc(1UL, sizeof(*_out_ptr))));
    liba_initialize_fn(_d, _dt, _tStr, _size, _out_ptr);
    _out_ptr->_internal._is_allocated = true;
    return _out_ptr;
}


static inline void
liba_adelete_fn(Array *restrict _a, void (*_callback_freeing_ptr)(void*,size_t))
{
    _internalArray *restrict _iptr;

    if (!!_a) {
        _iptr = &_a->_internal;
        if (!!_iptr->_d) {
            if (__TypePtr == _iptr->_dt && !!_callback_freeing_ptr)
                _callback_freeing_ptr(_iptr->_d->ptr, _iptr->_nEl * _iptr->_tSize);
            free(_iptr->_d);
        }
        free(_iptr->_tStr);
        if (_iptr->_is_allocated)
            free(_a);
    }
}

# endif /* S_ARRAY */

#endif /* LIBA_INTERNAL_H */
