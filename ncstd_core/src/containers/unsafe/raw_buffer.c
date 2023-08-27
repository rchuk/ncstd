#include "ncstd/containers/unsafe/raw_buffer.h"

#include <stdbool.h>
#include <string.h>

#include "ncstd/memory.h"


static bool nc_p_raw_buffer_contains_index(const NC_RawBuffer* self, size_t index) {
    return index < self->p.capacity;
}

static bool nc_p_raw_buffer_contains_range(const NC_RawBuffer* self, size_t index, size_t count, size_t object_size) {
    (void)object_size;

    return index + count <= self->p.capacity;
}

void* nc_raw_buffer_data(const NC_RawBuffer* self) {
    return self->p.data;
}

size_t nc_raw_buffer_capacity(const NC_RawBuffer* self) {
    return self->p.capacity;
}

void* nc_raw_buffer_get(const NC_RawBuffer* self, size_t index, size_t object_size) {
    if (!nc_p_raw_buffer_contains_index(self, index))
        return NULL;

    return nc_raw_buffer_get_unchecked(self, index, object_size);
}

void* nc_raw_buffer_get_unchecked(const NC_RawBuffer* self, size_t index, size_t object_size) {
    return nc_raw_buffer_get_multiple_unchecked(self, index, 1, object_size);
}

void* nc_raw_buffer_get_multiple(const NC_RawBuffer* self, size_t index, size_t count, size_t object_size) {
    if (count == 0 || !nc_p_raw_buffer_contains_range(self, index, count, object_size))
        return NULL;

    return nc_raw_buffer_get_multiple_unchecked(self, index, count, object_size);
}

void* nc_raw_buffer_get_multiple_unchecked(const NC_RawBuffer* self, size_t index, size_t count, size_t object_size) {
    (void)count;

    return self->p.data + index * object_size;
}

void nc_raw_buffer_set(NC_RawBuffer* self, const void* object, size_t index, size_t object_size) {
    if (!nc_p_raw_buffer_contains_index(self, index))
        return;

    nc_raw_buffer_set_unchecked(self, object, index, object_size);
}

void nc_raw_buffer_set_unchecked(NC_RawBuffer* self, const void* object, size_t index, size_t object_size) {
    nc_raw_buffer_set_multiple_unchecked(self, object, index, 1, object_size);
}

void nc_raw_buffer_set_multiple(NC_RawBuffer* self, const void* objects, size_t index, size_t count, size_t object_size) {
    if (count == 0 || !nc_p_raw_buffer_contains_range(self, index, count, object_size))
        return;

    nc_raw_buffer_set_multiple_unchecked(self, objects, index, count, object_size);
}

void nc_raw_buffer_set_multiple_unchecked(NC_RawBuffer* self, const void* objects, size_t index, size_t count, size_t object_size) {
    uint8_t* const buffer_data = nc_raw_buffer_get_unchecked(self, index, object_size);
    memcpy(buffer_data, objects, count * object_size);
}

void nc_raw_buffer_resize_unchecked(NC_RawBuffer* self, size_t new_capacity, size_t object_size) {
    self->p.data = nc_realloc(self->p.data, new_capacity * object_size);
    self->p.capacity = new_capacity;
}

void nc_raw_buffer_grow_amorthized(NC_RawBuffer* self, size_t required_capacity, size_t growth_factor, size_t object_size) {
    //
    if (required_capacity < nc_raw_buffer_capacity(self))
        return;
    //
    
    //into separate funcs

    //TODO: use max function
    const size_t grown_capacity = nc_raw_buffer_capacity(self) * growth_factor;
    const size_t new_capacity = required_capacity < grown_capacity ? grown_capacity : required_capacity; 
    //

    nc_raw_buffer_resize_unchecked(self, new_capacity, object_size);
}


NC_RawBuffer nc_raw_buffer_init(size_t object_size) {
    (void)object_size;

    return (NC_RawBuffer) {
        .p = {
            .data = NULL,
            .capacity = 0
        }
    };
}

NC_RawBuffer nc_raw_buffer_init_with_capacity(size_t capacity, size_t object_size) {
    return (NC_RawBuffer) {
        .p = {
            .data = nc_malloc(capacity * object_size),
            .capacity = capacity
        }
    };
}

NC_RawBuffer nc_raw_buffer_init_with_objects(const void* objects, size_t count, size_t object_size) {
    NC_RawBuffer raw_buffer = nc_raw_buffer_init_with_capacity(count, object_size);
    nc_raw_buffer_set_multiple_unchecked(&raw_buffer, objects, 0, count, object_size);

    return raw_buffer;
}

void nc_raw_buffer_free(NC_RawBuffer* self) {
    if (!self)
        return;
        
    nc_free(self->p.data);
}