#ifndef LIBI_TYPES_H
# define LIBI_TYPES_H

# ifndef LIBI_INTERNAL_TYPES
# error "inlcude only libinterface.h"
# endif

# include <stddef.h>
# include <stdbool.h>

# ifndef E_INTERFACE_DATA_TYPE_GENERIC
#  define E_INTERFACE_DATA_TYPE_GENERIC

typedef enum e_interface_data_type_generic InterfaceDataType;

enum    e_interface_data_type_generic {
    IDTC,   IDTCPtr,   // char               | char*
    IDTUC,  IDTUCPtr,  // unsigned char      | unsigned char*
    IDTS,   IDTSPtr,   // short              | short*
    IDTUS,  IDTUSPtr,  // unsigned short     | unsigned short*
    IDTI,   IDTIPtr,   // int                | int*
    IDTUI,  IDTUIPtr,  // unsigned int       | unsigned int*
    IDTL,   IDTLPtr,   // long               | long*
    IDTUL,  IDTULPtr,  // unsigned long      | unsigned long*
    IDTLL,  IDTLLPtr,  // long long          | long long*
    IDTULL, IDTULLPtr, // unsigned long long | unsigned long long*
    IDTD,   IDTDPtr,   // double             | double*
    IDTLD,  IDTLDPtr,  // long double        | long double*
    IDTF,   IDTFPtr,   // float              | float*
    IDTPtr             // void* or anything else
} __attribute__((packed));

// A-HYLE macros protect system
# undef libi_data_type_generic
# define libi_data_type_generic(x) _Generic((x) + 0,            \
    char:               IDTC,   char*:               IDTCPtr,   \
    unsigned char:      IDTUC,  unsigned char*:      IDTUCPtr,  \
    short:              IDTS,   short*:              IDTSPtr,   \
    unsigned short:     IDTUS,  unsigned short*:     IDTUSPtr,  \
    int:                IDTI,   int*:                IDTIPtr,   \
    unsigned int:       IDTUI,  unsigned int*:       IDTUIPtr,  \
    long:               IDTL,   long*:               IDTLPtr,   \
    unsigned long:      IDTUL,  unsigned long*:      IDTULPtr,  \
    long long:          IDTLL,  long long*:          IDTLLPtr,  \
    unsigned long long: IDTULL, unsigned long long*: IDTULLPtr, \
    double:             IDTD,   double*:             IDTDPtr,   \
    long double:        IDTLD,  long double*:        IDTLDPtr,  \
    float:              IDTF,   float*:              IDTFPtr,   \
    default:            IDTPtr)

# endif /* E_INTERFACE_DATA_TYPE_GENERIC */

# ifndef U_INTERACE_DATA_GENERIC
#  define U_INTERACE_DATA_GENERIC

typedef union u_interface_data_generic InterfaceData;

union   u_interface_data_generic
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

# undef InterfaceGetData
# define InterfaceGetData(type, __i) _Generic((type)0,                        \
    char:               (__i).id->c,   char*:               (__i).id->cptr,   \
    unsigned char:      (__i).id->uc,  unsigned char*:      (__i).id->ucptr,  \
    short:              (__i).id->s,   short*:              (__i).id->sptr,   \
    unsigned short:     (__i).id->us,  unsigned short*:     (__i).id->usptr,  \
    int:                (__i).id->i,   int*:                (__i).id->iptr,   \
    unsigned int:       (__i).id->ui,  unsigned int*:       (__i).id->uiptr,  \
    long:               (__i).id->l,   long*:               (__i).id->lptr,   \
    unsigned long:      (__i).id->ul,  unsigned long*:      (__i).id->ulptr,  \
    long long:          (__i).id->ll,  long long*:          (__i).id->llptr,  \
    unsigned long long: (__i).id->ull, unsigned long long*: (__i).id->ullptr, \
    double:             (__i).id->d,   double*:             (__i).id->dptr,   \
    long double:        (__i).id->ld,  long double*:        (__i).id->ldptr,  \
    float:              (__i).id->f,   float*:              (__i).id->fptr,   \
    default:            (__i).id->ptr)


# endif /* U_INTERACE_DATA_GENERIC */

# ifndef S_INTERFACE
#  define S_INTERFACE

typedef struct s_interface Interface;

typedef size_t  (*libi_fnptr_length)(const Interface *restrict);

struct s_interface {
    InterfaceData *restrict id;
    char *restrict          tStr;
    size_t                  size;
    size_t                  n_el;
    libi_fnptr_length       length;
    InterfaceDataType       idt;
    bool                    __is_allocated;
} __attribute__((aligned(__BIGGEST_ALIGNMENT__)));

static inline size_t
libi_length(const Interface *restrict i)
{
    return i->n_el;
}

# endif /* S_INTERFACE */

#endif /* LIBI_TYPES_H */
