#include "ncstd/nc_string.h"

#include "ncstd/utf8.h"


static const size_t STRING_GROWTH_FACTOR = 2;
static const char NULL_TERMINATOR = '\0';


void nc_p_string_terminate_unchecked(NC_String* self) {
    nc_raw_buffer_set_unchecked(&self->p.raw_buffer, &NULL_TERMINATOR, self->p.size, sizeof(char));
}

bool nc_string_is_empty(const NC_String* self) {
    return nc_string_size(self) == 0;
}

size_t nc_string_size(const NC_String* self) {
    return self->p.size;
}

size_t nc_string_capacity(const NC_String* self) {
    return nc_raw_buffer_capacity(&self->p.raw_buffer);
}


void nc_string_clear(NC_String* self) {
    if (self->p.size == 0)
        return;

    self->p.size = 0;
    nc_p_string_terminate_unchecked(self);
}

void nc_string_reserve(NC_String* self, size_t new_capacity) {
    nc_raw_buffer_grow_amorthized(&self->p.raw_buffer, new_capacity + 1, STRING_GROWTH_FACTOR, sizeof(char));
}

NC_OPTION(char32_t) nc_string_pop(NC_String* self) {
    if (nc_string_is_empty(self))
        return nc_option_char32_init_none();

    for (size_t i = self->p.size - 1; i >= 0; --i) {
        // TODO: add indexing function
        const uint8_t* const byte = nc_raw_buffer_get(&self->p.raw_buffer, i, sizeof(char));

        if (!nc_utf8_is_continuation_byte(*byte)) {
            size_t char_width = 0;
            const char32_t ch = nc_utf8_decode_char_unchecked(byte, &char_width);
            self->p.size -= char_width;

            nc_p_string_terminate_unchecked(self);

            return nc_option_char32_init_some(ch);
        }
    }

    return nc_option_char32_init_none();
    
    // NOTE: Unreachable. Create some kind of an assertion
}

void nc_string_push_unchecked(NC_String* self, char32_t ch) {
    nc_string_reserve(self, self->p.size + 4);

    self->p.size += nc_utf8_encode_char_unchecked(nc_raw_buffer_data(&self->p.raw_buffer), ch);
}

void nc_string_push_string_view(NC_String* self, NC_StringView string_view) {
    const char* const bytes = nc_string_view_bytes(string_view);
    const size_t size = nc_string_view_size(string_view);

    nc_string_reserve(self, self->p.size + size);
    
    nc_raw_buffer_set_multiple_unchecked(&self->p.raw_buffer, bytes, self->p.size, size, sizeof(char));
    self->p.size += size;
    nc_p_string_terminate_unchecked(self);
}


NC_String nc_string_empty() {
    NC_RawBuffer raw_buffer = nc_raw_buffer_init_with_objects(&NULL_TERMINATOR, 1, sizeof(char));

    return (NC_String) { .p = { .raw_buffer = raw_buffer, .size = 0 } };
}


// TODO: Check for 0 capacity
NC_String nc_string_with_capacity(size_t capacity) {
    NC_RawBuffer raw_buffer = nc_raw_buffer_init_with_capacity(capacity, sizeof(char));
    nc_raw_buffer_set_unchecked(&raw_buffer, &NULL_TERMINATOR, 0, sizeof(char));

    return (NC_String) { .p = { .raw_buffer = raw_buffer, .size = 0 } };
}

NC_OPTION(NC_String) nc_string_from_c_str(const char* c_str) {
    const size_t length = strlen(c_str);

    if (!nc_utf8_is_valid((const uint8_t*)c_str, length))
        return nc_option_string_init_none();

    return nc_option_string_init_some(nc_string_from_c_str_unchecked(c_str));
}

NC_String nc_string_from_c_str_unchecked(const char* c_str) {
    const size_t length = strlen(c_str);
    NC_RawBuffer raw_buffer = nc_raw_buffer_init_with_objects(c_str, length + 1, sizeof(char));

    return (NC_String) { .p = { .raw_buffer = raw_buffer, .size = length } };
}

NC_String nc_string_from_string_view(NC_StringView string_view) {
    return nc_string_with_length_unchecked(nc_string_view_bytes(string_view), nc_string_view_size(string_view));
}

NC_String nc_string_with_length_unchecked(const char* chars, size_t length) {
    NC_RawBuffer raw_buffer = nc_raw_buffer_init_with_capacity(length + 1, sizeof(char));
    nc_raw_buffer_set_multiple_unchecked(&raw_buffer, chars, 0, length, sizeof(char));
    nc_raw_buffer_set_unchecked(&raw_buffer, &NULL_TERMINATOR, length, sizeof(char));

    return (NC_String) { .p = { .raw_buffer = raw_buffer, .size = length } };
}

void nc_string_destroy(NC_String* self) {
    if (!self)
        return;

    nc_raw_buffer_free(&self->p.raw_buffer);
}


#if NC_FEATURE_ITERATOR


#endif