#include "ncstd/util/create_util.h"


extern inline void* nc_util_create_with(void* self_init, size_t size);
extern inline void* nc_util_create_with_flexible(void* self_init, size_t size, void* flexible_init, size_t flexible_size);