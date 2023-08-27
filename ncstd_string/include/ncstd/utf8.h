#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <uchar.h>


//bool nc_utf8_is_leading_byte(uint8_t byte);
bool nc_utf8_is_continuation_byte(uint8_t byte);
size_t nc_utf8_character_width(uint8_t byte);
size_t nc_utf8_character_width_unchecked(uint8_t byte);
bool nc_is_valid_unicode_codepoint(char32_t ch);

size_t nc_utf8_encode_char(uint8_t* data, char32_t ch);
size_t nc_utf8_encode_char_unchecked(uint8_t* data, char32_t ch);
char32_t nc_utf8_decode_char_unchecked(const uint8_t* data, size_t* out_bytes_consumed); // NOTE: Add checked version?

bool nc_utf8_is_valid(const uint8_t* data, size_t size);
