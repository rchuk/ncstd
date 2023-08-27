#include "ncstd/iterators/pointer_iterator.h"


static void* nc_pointer_iterator_next_untyped(void* iterator) {
	return nc_pointer_iterator_next(iterator);
}

const static NC_IteratorVtable ITERATOR_VTABLE = {
	.next_fn = nc_pointer_iterator_next_untyped
};


void* nc_pointer_iterator_next(NC_PointerIterator* self) {
	if (self->p.current >= self->p.end)
		return NULL;

	void* const next = self->p.current;

	self->p.current += self->p.object_size;

	return next;
}

NC_Iterator* nc_pointer_iterator_into_dyn(NC_PointerIterator self) {
	return nc_iterator_create(&ITERATOR_VTABLE, &self, sizeof self);
}


NC_PointerIterator nc_pointer_iterator_init(void* start_ptr, size_t length, size_t object_size) {
	return (NC_PointerIterator) {
		.p = {
			.current = start_ptr,
			.end = (uint8_t*)start_ptr + length * object_size,
			.object_size = object_size
		}
	};
}