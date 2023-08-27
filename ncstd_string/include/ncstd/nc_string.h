#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "ncstd/string_view.h"
#include "ncstd/macros/option_macros.h"
#include "ncstd/containers/unsafe/raw_buffer.h"


typedef struct {
	struct {
		NC_RawBuffer raw_buffer;
		size_t size; // Size in bytes, not utf-8 codepoints
	} p;
} NC_String;

NC_DEFINE_OPTION(NC_String, string)


NC_String nc_string_empty();
NC_String nc_string_with_capacity(size_t capacity);
/** @memberof NC_String 
 * @brief Test docs
 * */
NC_OPTION(NC_String) nc_string_from_c_str(const char* c_str);
NC_String nc_string_from_c_str_unchecked(const char* c_str);
NC_String nc_string_from_string_view(NC_StringView string_view);
NC_String nc_string_with_length_unchecked(const char* chars, size_t length);

void nc_string_destroy(NC_String* self);


bool nc_string_is_empty(const NC_String* self);
size_t nc_string_size(const NC_String* self);
size_t nc_string_capacity(const NC_String* self);

void nc_string_clear(NC_String* self);

void nc_string_reserve(NC_String* self, size_t new_capacity);

//char32_t nc_string_pop(NC_String* self); // TODO
NC_OPTION(char32_t) nc_string_pop(NC_String* self);
void nc_string_push_unchecked(NC_String* self, char32_t ch);
void nc_string_push_string_view(NC_String* self, NC_StringView string_view);

// TODO: 
// join function,
// repeat function,
// shrink (to fit)
// truncate (similar to slice),
// add slicing with utf8 index?


#if NC_FEATURE_ITERATOR

// TODO: codepoint iterator, joining strings

#endif
