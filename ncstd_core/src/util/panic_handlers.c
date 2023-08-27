#include "ncstd/util/panic_handlers.h"

#include <stdlib.h>


void nc_default_handle_out_of_memory() {
    abort();
}

//TODO make it configurable
void nc_handle_out_of_memory() {
#ifdef NC_USER_HANDLE_OUT_OF_MEMORY
    nc_user_handle_out_of_memory();
#else
    nc_default_handle_out_of_memory();
#endif
}