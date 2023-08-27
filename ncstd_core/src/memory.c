#include "ncstd/memory.h"

#include <stdlib.h>

#include "ncstd/util/panic_handlers.h"


void* nc_malloc(size_t size) {
    void* const ptr = malloc(size);
    if (ptr == NULL)
        nc_handle_out_of_memory();

    return ptr;
}

void* nc_calloc(size_t count, size_t object_size) {
    void* const ptr = calloc(count, object_size);
    if (ptr == NULL)
        nc_handle_out_of_memory();

    return ptr;
}

void* nc_realloc(void* ptr, size_t new_size) {
    void* const new_ptr = realloc(ptr, new_size);
    if (new_ptr == NULL) {
        nc_handle_out_of_memory();

        nc_free(ptr);
    }

    return new_ptr;
}

bool nc_realloc_preserving(void** in_out_ptr, size_t new_size) {
    void* const new_ptr = realloc(*in_out_ptr, new_size);
    if (new_ptr == NULL) {
        nc_handle_out_of_memory();
        
        return false;
    }

    *in_out_ptr = new_ptr;

    return true;
}

void nc_free(void* ptr) {
    free(ptr);
}