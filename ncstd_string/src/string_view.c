#include "ncstd/string_view.h"

#include <string.h>


bool nc_option_string_view_is_some(NC_OPTION(NC_StringView) self) {
    return self.value.p.cstr;
}

NC_OPTION(NC_StringView) nc_option_string_view_init_some(NC_StringView string_view) {
    return (NC_OPTION(NC_StringView)) { .value = string_view };
}

NC_OPTION(NC_StringView) nc_option_string_view_init_none() {
    return (NC_OPTION(NC_StringView)) { .value = nc_string_view_init_unchecked(NULL, 0) };
}


const char* nc_string_view_bytes(NC_StringView self) {
    return self.p.cstr;
}

size_t nc_string_view_size(NC_StringView self) {
    return self.p.size;
}


bool nc_string_view_eq(NC_StringView a, NC_StringView b) {
    if (nc_string_view_size(a) != nc_string_view_size(b))
        return false;

    return strncmp(nc_string_view_bytes(a), nc_string_view_bytes(b), nc_string_view_size(a));
}

bool nc_string_view_ptr_eq(const void* a, const void* b, void* data) {
    (void)data;

    return nc_string_view_eq(*(const NC_StringView*)a, *(const NC_StringView*)b);
}

// TODO: Use UTF-8 validation
NC_StringView nc_string_view_init_unchecked(const char* cstr, size_t size) {
    return (NC_StringView) { 
        .p = {
            .cstr = cstr,
            .size = size
        }
    };
}

// TODO: Use UTF-8 validation
NC_StringView nc_string_view_from_cstr(const char* cstr) {
    return (NC_StringView) { 
        .p = {
            .cstr = cstr,
            .size = strlen(cstr)
        }
    };
}


#if NC_FEATURE_ITERATOR

NC_CharsIterator nc_string_view_chars_iter(NC_StringView self) {
    return nc_chars_iterator_init(self.p.cstr, self.p.size);
}

#endif