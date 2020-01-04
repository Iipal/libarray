#ifndef LIBI_GENERIC_FUNCTIONS_H
# define LIBI_GENERIC_FUNCTIONS_H

# if !(defined LIBI_INTERNAL || defined LIBI_INTERNAL_H)
#  error "include only libinterface.h"
# endif

# include <stddef.h>

size_t  libi_c_length  (void *restrict data);
size_t  libi_s_length  (void *restrict data);
size_t  libi_i_length  (void *restrict data);
size_t  libi_l_length  (void *restrict data);
size_t  libi_ll_length (void *restrict data);
size_t  libi_uc_length (void *restrict data);
size_t  libi_us_length (void *restrict data);
size_t  libi_ui_length (void *restrict data);
size_t  libi_ul_length (void *restrict data);
size_t  libi_d_length  (void *restrict data);
size_t  libi_ld_length (void *restrict data);
size_t  libi_f_length  (void *restrict data);
size_t  libi_ptr_length(void *restrict data);

#endif /* LIBI_GENERIC_FUNCTIONS_H */
