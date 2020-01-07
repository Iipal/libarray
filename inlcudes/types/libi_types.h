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
    unsigned int        ui;  unsigned int        *iuptr;
    long                l;   long                *lptr;
    unsigned long       ul;  unsigned long       *ulptr;
    long long           ll;  long long           *llptr;
    unsigned long long  ull; unsigned long long  *ullptr;
    double              d;   double              *dptr;
    long double         ld;  long double         *ldptr;
    float               f;   float               *fptr;
    void                *ptr;
};

// A-HYLE macros protect system
# undef libi_dup_static_id
# undef libi_dup_ptr_id

# define libi_dup_static_id(x) \
    (InterfaceData*)memcpy(calloc(1UL, sizeof(x)), &x, sizeof(x))
# define libi_dup_ptr_id(x) \
    (InterfaceData*)memcpy(calloc(1UL, sizeof(*x)), x, sizeof(*x))

# endif /* U_INTERACE_DATA_GENERIC */

# ifndef S_INTERFACE
#  define S_INTERFACE

typedef struct s_interface Interface;

struct s_interface {
    InterfaceData *restrict id;
    char *restrict          tStr;
    size_t                  size;
    InterfaceDataType       idt;
    bool                    __is_allocated;
} __attribute__((aligned(__BIGGEST_ALIGNMENT__)));

# endif /* S_INTERFACE */

#endif /* LIBI_TYPES_H */
