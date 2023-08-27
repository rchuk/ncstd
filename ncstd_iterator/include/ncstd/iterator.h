#pragma once

#include <stdint.h>


typedef struct {
	void* (* const next_fn)(void* iterator);
} NC_IteratorVtable;

// NOTE: Make it as a template instead?
typedef struct {
	const NC_IteratorVtable* const vtable;
	uint8_t concrete[];
} NC_Iterator;

void* nc_iterator_concrete(NC_Iterator* self);
void* nc_iterator_next(NC_Iterator* self);
// TODO: Implement peek

NC_Iterator* nc_iterator_create(const NC_IteratorVtable* vtable, void* concrete, size_t concrete_size);