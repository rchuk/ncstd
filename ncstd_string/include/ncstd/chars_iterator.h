#pragma once

#include "ncstd/iterator.h"

#include <uchar.h>


// TODO: Put it behind compilation flag

typedef struct {
    struct {
        uint8_t* current;
        uint8_t* const end;

        char32_t current_char;
    } p;
} NC_CharsIterator;


NC_CharsIterator nc_chars_iterator_init(void* start_ptr, size_t length);

void* nc_chars_iterator_next(NC_CharsIterator* self);

NC_CharsIterator* nc_chars_iterator_into_dyn(NC_CharsIterator self);
