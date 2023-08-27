#include "ncstd/chars_iterator.h"

#include "ncstd/utf8.h"


static void* nc_chars_iterator_next_untyped(void* iterator) {
	return nc_chars_iterator_next(iterator);
}

const static NC_IteratorVtable ITERATOR_VTABLE = {
	.next_fn = nc_chars_iterator_next_untyped
};


void* nc_chars_iterator_next(NC_CharsIterator* self) {
    if (self->p.current >= self->p.end)
        return NULL;

    size_t char_width = 0;
    self->p.current_char = nc_utf8_decode_char_unchecked(self->p.current, &char_width);
    self->p.current += char_width;

    return &self->p.current_char;
}

NC_CharsIterator* nc_chars_iterator_into_dyn(NC_CharsIterator self) {
    return nc_iterator_create(&ITERATOR_VTABLE, &self, sizeof self);
}

NC_CharsIterator nc_chars_iterator_init(void* start_ptr, size_t length) {
    return (NC_CharsIterator) {
		.p = {
			.current = start_ptr,
			.end = (uint8_t*)start_ptr + length,
            .current_char = '\0'
		}
	};
}