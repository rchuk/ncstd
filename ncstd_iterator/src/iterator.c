#include "ncstd/iterator.h"

#include "ncstd/util/create_util.h"


void* nc_iterator_concrete(NC_Iterator* self) {
	return self->concrete;
}

void* nc_iterator_next(NC_Iterator* self) {
	return self->vtable->next_fn(nc_iterator_concrete(self));
}


NC_Iterator* nc_iterator_create(const NC_IteratorVtable* vtable, void* concrete, size_t concrete_size) {
	return nc_util_create_with_flexible(
		&(NC_Iterator) { .vtable = vtable },
		sizeof(NC_Iterator),
		concrete,
		concrete_size
	);
}