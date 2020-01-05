#ifndef LIBINTERFACE_H
# define LIBINTERFACE_H

# define _GNU_SOURCE

# include <stdlib.h>
# include <stddef.h>
# include <assert.h>
# include <string.h>
# include <strings.h>
# include <err.h>
# include <stdbool.h>

# ifndef E_INTERFACE_DATA_TYPE_GENERIC
#  define E_INTERFACE_DATA_TYPE_GENERIC
enum    e_interface_data_type_generic {
    IDTC,  IDTUC,
    IDTS,  IDTUS,
    IDTI,  IDTUI,
    IDTL,  IDTUL,
    IDTLL, IDTULL,
    IDTD,  IDTLD,
    IDTF,
    IDTPtr
} __attribute__((packed));
typedef enum e_interface_data_type_generic InterfaceDataType;
# endif /* E_INTERFACE_DATA_TYPE_GENERIC */

# ifndef U_INTERACE_DATA_GENERIC
#  define U_INTERACE_DATA_GENERIC
union   u_interface_data_generic
{
    char        c;  unsigned char       uc;
    short       s;  unsigned short      us;
    int         i;  unsigned int        ui;
    long        l;  unsigned long       ul;
    double      d;  long double         ld;
    long long   ll; unsigned long long  ull;
    float       f;
    void        *ptr;
};
typedef union u_interface_data_generic InterfaceData;
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

# define libi_generic_get_type(x) _Generic((x),   \
    char:      IDTC,  unsigned char:      IDTUC,  \
    short:     IDTS,  unsigned short:     IDTUS,  \
    int:       IDTI,  unsigned int:       IDTUI,  \
    long:      IDTL,  unsigned long:      IDTUL,  \
    long long: IDTLL, unsigned long long: IDTULL, \
    double:    IDTD,  long double:        IDTLD,  \
    float:     IDTF,                              \
    default:   IDTPtr)

# define IInitialize(type, data, dst_ptr) \
    libi_initialize_fn((InterfaceData)data, \
        libi_generic_get_type(data), #type, sizeof(type), dst_ptr)

# define libi_dup_static_id(x) \
    (InterfaceData*)memcpy(calloc(1UL, sizeof(x)), &x, sizeof(x))
# define libi_dup_ptr_id(x) \
    (InterfaceData*)memcpy(calloc(1UL, sizeof(*x)), x, sizeof(*x))

static inline void
libi_initialize_fn(InterfaceData __id,
                   InterfaceDataType __idt,
                   const char *restrict __tStr,
                   const size_t __size,
                   Interface *restrict __dst)
{
    assert(!(IDTPtr == __idt && NULL == __id.ptr));
    *__dst = (Interface) {
        libi_dup_static_id(__id), strdup(__tStr), __size, __idt, false
    };
}

# define INew(type, data) \
    libi_fn_inew((InterfaceData)data, \
        libi_generic_get_type(data), #type, sizeof(type))

static inline Interface
*libi_fn_inew(InterfaceData __id,
              InterfaceDataType __idt,
              const char *restrict __tStr,
              const size_t __size)
{
    Interface   *__out_ptr;

    assert((__out_ptr = calloc(1UL, sizeof(*__out_ptr))));
    IInitialize_fn(__id, __idt, __tStr, __size, __out_ptr);
    __out_ptr->__is_allocated = true;
    return __out_ptr;
}

static inline void
IDelete(Interface *restrict __i, void (*__callback_freeing_ptr)(void*,size_t)) {
    if (__i) {
        if (__i->id) {
            if (IDTPtr == __i->idt && __callback_freeing_ptr)
                __callback_freeing_ptr(__i->id->ptr, __i->size);
            free(__i->id);
        }
        free(__i->tStr);
        if (__i->__is_allocated)
            free(__i);
    }
}

#endif /* LIBINTERFACE_H */
