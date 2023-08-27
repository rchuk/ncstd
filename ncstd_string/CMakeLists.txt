cmake_minimum_required(VERSION 3.12)


project(ncstd_string)


add_library(ncstd_string OBJECT
    "include/ncstd/nc_string.h"
    "include/ncstd/string_view.h"
    "include/ncstd/utf8.h"


    "include/ncstd/chars_iterator.h"
    "src/chars_iterator.c"
    

    "src/string.c"
    "src/string_view.c"
    "src/utf8.c"
)

target_include_directories(ncstd_string PUBLIC include)
target_include_directories(ncstd_string PRIVATE include/ncstd)
target_include_directories(ncstd_string PRIVATE src)

target_link_libraries(ncstd_string PUBLIC ncstd_core)


if (NCSTD_FEATURE_ENABLE_ITERATOR)
    target_link_libraries(ncstd_string PUBLIC ncstd_iterator)
endif()