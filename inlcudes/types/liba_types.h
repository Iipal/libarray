#ifndef LIBA_TYPES_H
# define LIBA_TYPES_H

# ifndef LIBA_INTERNAL
# error "inlcude only libinterface.h"
# endif

# include <stddef.h>
# include <stdbool.h>

# ifndef E_ARRAY_DATA_TYPE
#  define E_ARRAY_DATA_TYPE

typedef enum e_array_data_type ArrayDataType;

enum    e_array_data_type {
    ADT_C,   ADT_CPtr,   // char               | char*
    ADT_UC,  ADT_UCPtr,  // unsigned char      | unsigned char*
    ADT_S,   ADT_SPtr,   // short              | short*
    ADT_US,  ADT_USPtr,  // unsigned short     | unsigned short*
    ADT_I,   ADT_IPtr,   // int                | int*
    ADT_UI,  ADT_UIPtr,  // unsigned int       | unsigned int*
    ADT_L,   ADT_LPtr,   // long               | long*
    ADT_UL,  ADT_ULPtr,  // unsigned long      | unsigned long*
    ADT_LL,  ADT_LLPtr,  // long long          | long long*
    ADT_ULL, ADT_ULLPtr, // unsigned long long | unsigned long long*
    ADT_D,   ADT_DPtr,   // double             | double*
    ADT_LD,  ADT_LDPtr,  // long double        | long double*
    ADT_F,   ADT_FPtr,   // float              | float*
    ADT_Ptr              // void* or anything else
} __attribute__((packed));

# undef liba_get_data_type
# define liba_get_data_type(x) _Generic((x) + 0,                  \
    char:               ADT_C,   char*:               ADT_CPtr,   \
    unsigned char:      ADT_UC,  unsigned char*:      ADT_UCPtr,  \
    short:              ADT_S,   short*:              ADT_SPtr,   \
    unsigned short:     ADT_US,  unsigned short*:     ADT_USPtr,  \
    int:                ADT_I,   int*:                ADT_IPtr,   \
    unsigned int:       ADT_UI,  unsigned int*:       ADT_UIPtr,  \
    long:               ADT_L,   long*:               ADT_LPtr,   \
    unsigned long:      ADT_UL,  unsigned long*:      ADT_ULPtr,  \
    long long:          ADT_LL,  long long*:          ADT_LLPtr,  \
    unsigned long long: ADT_ULL, unsigned long long*: ADT_ULLPtr, \
    double:             ADT_D,   double*:             ADT_DPtr,   \
    long double:        ADT_LD,  long double*:        ADT_LDPtr,  \
    float:              ADT_F,   float*:              ADT_FPtr,   \
    default:            ADT_Ptr)

# endif /* E_ARRAY_DATA_TYPE */

# ifndef U_ARRAY_DATA
#  define U_ARRAY_DATA

typedef union u_array_data ArrayData;

union   u_array_data
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

# undef ArrayGetDataAt
# define ArrayGetDataAt(type, __a, __at) _Generic((type)0,                                  \
    char:               (__a).ad[(__at)].c,   char*:               (__a).ad[(__at)].cptr,   \
    unsigned char:      (__a).ad[(__at)].uc,  unsigned char*:      (__a).ad[(__at)].ucptr,  \
    short:              (__a).ad[(__at)].s,   short*:              (__a).ad[(__at)].sptr,   \
    unsigned short:     (__a).ad[(__at)].us,  unsigned short*:     (__a).ad[(__at)].usptr,  \
    int:                (__a).ad[(__at)].i,   int*:                (__a).ad[(__at)].iptr,   \
    unsigned int:       (__a).ad[(__at)].ui,  unsigned int*:       (__a).ad[(__at)].uiptr,  \
    long:               (__a).ad[(__at)].l,   long*:               (__a).ad[(__at)].lptr,   \
    unsigned long:      (__a).ad[(__at)].ul,  unsigned long*:      (__a).ad[(__at)].ulptr,  \
    long long:          (__a).ad[(__at)].ll,  long long*:          (__a).ad[(__at)].llptr,  \
    unsigned long long: (__a).ad[(__at)].ull, unsigned long long*: (__a).ad[(__at)].ullptr, \
    double:             (__a).ad[(__at)].d,   double*:             (__a).ad[(__at)].dptr,   \
    long double:        (__a).ad[(__at)].ld,  long double*:        (__a).ad[(__at)].ldptr,  \
    float:              (__a).ad[(__at)].f,   float*:              (__a).ad[(__at)].fptr,   \
    default:            (__a).ad[(__at)].ptr)

# endif /* U_ARRAY_DATA */

# ifndef S_ARRAY
#  define S_ARRAY

typedef struct s_array Array;

typedef size_t  (*liba_fnptr_length)(const Array *restrict);

struct s_array {
    ArrayData *restrict ad;
    char *restrict      tStr;
    size_t              size;
    size_t              n_el;
    liba_fnptr_length   length;
    ArrayDataType       adt;
    bool                __is_allocated;
} __attribute__((aligned(__BIGGEST_ALIGNMENT__)));

static size_t
liba_length(const Array *restrict a)
{
    return a->n_el;
}

# endif /* S_ARRAY */

#endif /* LIBA_TYPES_H */
