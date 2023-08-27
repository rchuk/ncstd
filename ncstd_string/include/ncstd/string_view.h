#pragma once

/**
 * @file
*/

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "ncstd/macros/option_macros.h"

#if NC_FEATURE_ITERATOR
#include "ncstd/chars_iterator.h"
#endif


// TODO: Move it into files with options for builtin types
NC_DEFINE_OPTION(char32_t, char32)

typedef struct {
    struct {
        const char* cstr;
        size_t size;
    } p;
} NC_StringView;

typedef struct {
    NC_StringView value;
} NC_OPTION(NC_StringView);

NC_OPTION(NC_StringView) nc_option_string_view_init_some(NC_StringView string_view);
NC_OPTION(NC_StringView) nc_option_string_view_init_none();
bool nc_option_string_view_is_some(NC_OPTION(NC_StringView) self);


// TODO: create UTF-8 codepoint iterator, length getter function, slicing functions
/*
StringView string_view_slice(StringView string_view, size_t begin, size_t end);
StringView string_view_slice_begin(StringView string_view, size_t size);
StringView string_view_slice_end(StringView string_view, size_t size);
*/

NC_StringView nc_string_view_init_unchecked(const char* cstr, size_t size);
NC_StringView nc_string_view_from_cstr(const char* cstr); // TODO: add unchecked variant

const char* nc_string_view_bytes(NC_StringView self);
size_t nc_string_view_size(NC_StringView self);


// TODO: create trim functions
/*
NC_StringView nc_string_view_trim(NC_StringView self);
NC_StringView nc_string_view_trim_start(NC_StringView self);
NC_StringVIew nc_string_view_trim_end(NC_StringView self);
NC_StringView nc_string_view_trim_matches(NC_StringView self, NC_StringView match);
NC_StringView nc_string_view_trim_start_matches(NC_StringView self, NC_StringView match);
NC_StringView nc_string_view_trim_end_matches(NC_StringView self, NC_StringView match);
*/

bool nc_string_view_eq(NC_StringView a, NC_StringView b);
bool nc_string_view_ptr_eq(const void* a, const void* b, void* data);


#if NC_FEATURE_ITERATOR

NC_CharsIterator nc_string_view_chars_iter(NC_StringView self);

#endif
