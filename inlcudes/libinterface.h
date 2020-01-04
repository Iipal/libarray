#ifndef LIBINTERFACE_H
# define LIBINTERFACE_H

# define LIBI_INTERNAL
# include "libi_internal.h"
# undef LIBI_INTERNAL

typedef struct s_interface* Interface;

# define INew(type, data) \
    libi_internal_create_interface(type, data)

#endif /* LIBINTERFACE_H */
