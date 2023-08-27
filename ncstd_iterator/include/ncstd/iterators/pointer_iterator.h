#pragma once

#include "ncstd/iterator.h"

#include <stddef.h>
#include <stdint.h>


typedef struct {
	struct {
		uint8_t* current;
		uint8_t* const end;

		const size_t object_size;
	} p;
} NC_PointerIterator;


NC_PointerIterator nc_pointer_iterator_init(void* start_ptr, size_t length, size_t object_size);

void* nc_pointer_iterator_next(NC_PointerIterator* self);

NC_Iterator* nc_pointer_iterator_into_dyn(NC_PointerIterator self);