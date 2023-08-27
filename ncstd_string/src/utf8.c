#include "ncstd/utf8.h"


static const uint8_t CONTINUATION_BYTE_MARKER = 0b10000000;
static const uint8_t CONTINUATION_BYTE_MASK = 0b00111111;


static uint8_t nc_p_leading_byte_mask(uint8_t char_width) {
    return 0xFF >> (char_width + 1);
}

static uint8_t nc_p_leading_byte_marker(uint8_t char_width) {
    return ~(0xFF >> char_width);
}

/*
bool nc_utf8_is_leading_byte(uint8_t byte) {
    return nc_utf8_character_width(byte) != 0;
}
*/

bool nc_utf8_is_continuation_byte(uint8_t byte) {
    return byte >= 0b10000000 && byte <= 0b10111111;
}

size_t nc_utf8_character_width(uint8_t byte) {
    if (byte < 0x80) { 
        return 1;
    } else if (byte >= 0b11000000 && byte <= 0b11011111) { 
        return 2;
    } else if (byte <= 0b11101111) {
        return 3;
    } else if (byte <= 0b11110111) { //or 0xF4 ?
        return 4;
    }
    
    return 0;
}

size_t nc_utf8_character_width_unchecked(uint8_t byte) {
    if (byte < 0x80) {
        return 1;
    } else if (byte <= 0b11011111) {
        return 2;
    } else if (byte <= 0b11101111) {
        return 3;
    } else {
        return 4;
    }
}

bool nc_is_valid_unicode_codepoint(char32_t ch) {
    if (ch > 0x10FFFF)
        return false;

    if (ch >= 0xD800 && ch <= 0xDFFF)
        return false;

    return true;
}

bool nc_utf8_is_valid(const uint8_t* data, size_t size) {
    size_t i = 0;
    while (i < size) {
        const uint8_t leading_byte = data[i++];

        const size_t char_width = nc_utf8_character_width(leading_byte);
        if (char_width == 1)
            continue;

        if (i + char_width - 1 >= size)
            return false;

        const uint8_t byte2 = data[i++];
        switch (char_width) {
            case 2:
                if (!nc_utf8_is_continuation_byte(byte2))
                    return false;

                break;
            
            case 3:
                if (leading_byte == 0xE0 && (byte2 < 0xA0 || byte2 > 0xBF) ||
                    leading_byte == 0xED && (byte2 < 0x80 || byte2 > 0x9F) ||
                    !nc_utf8_is_continuation_byte(byte2))
                    return false;

                if (!nc_utf8_is_continuation_byte(data[i++]))
                    return false;

                break;

            case 4:
                if (leading_byte == 0xF0 && (byte2 < 0x90 || byte2 > 0xBF) ||
                    leading_byte == 0xF3 && (byte2 < 0x80 || byte2 > 0x8F) ||
                    !nc_utf8_is_continuation_byte(byte2))
                    return false;

                if (!nc_utf8_is_continuation_byte(data[i++]))
                    return false;
                if (!nc_utf8_is_continuation_byte(data[i++]))
                    return false;

                break;

            default:
                return false;
        }
    }
    
    return true;
}

size_t nc_utf8_encode_char_unchecked(uint8_t* data, char32_t ch) {
    if (ch < 0x80) {
        data[0] = ch & 0x7F;

        return 1;
    }

    uint8_t char_width = 0;
    if (ch <= 0x07FF) { // 11 bits
        char_width = 2;
    } else if (ch <= 0xFFFF) { // 16 bits
        char_width = 3;
    } else if (ch <= 0x10FFFF) { // 21 bits
        char_width = 4;
    } else {
        return 0;
    }

    for (size_t i = char_width - 1; i >= 1; --i) {
        data[i] = CONTINUATION_BYTE_MARKER | (ch & CONTINUATION_BYTE_MASK);

        ch >>= 6;
    }

    const uint8_t leading_byte_marker = nc_p_leading_byte_marker(char_width);
    const uint8_t leading_byte_mask = nc_p_leading_byte_mask(char_width);

    data[0] = leading_byte_marker | (ch & leading_byte_mask);

    return char_width;    
}

size_t nc_utf8_encode_char(uint8_t* data, char32_t ch) {
    if (!nc_is_valid_unicode_codepoint(ch))
        return 0;
    
    return nc_utf8_encode_char_unchecked(data, ch);
}

char32_t nc_utf8_decode_char_unchecked(const uint8_t* data, size_t* out_bytes_consumed) {
    const uint8_t leading_byte = data[0];
    char32_t ch = leading_byte;

    const uint8_t char_width = nc_utf8_character_width_unchecked(leading_byte);
    *out_bytes_consumed = char_width;
    if (char_width == 1)
        return ch;

    // Remove first char_width + 1 bits from the result
    ch &= nc_p_leading_byte_mask(char_width);

    // Remove first 2 bits, and add 6 bits to the result
    for (size_t i = 1; i < char_width; ++i)
        ch = (ch << 6) | (data[i] & CONTINUATION_BYTE_MASK);

    return ch;
}