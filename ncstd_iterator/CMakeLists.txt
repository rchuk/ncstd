cmake_minimum_required(VERSION 3.12)


project(ncstd_iterator)


add_library(ncstd_iterator OBJECT
    "include/ncstd/iterators/pointer_iterator.h"
    "include/ncstd/iterator.h"

    "src/iterators/pointer_iterator.c"
    "src/iterator.c"
)

target_include_directories(ncstd_iterator PUBLIC include)
target_include_directories(ncstd_iterator PRIVATE include/ncstd)
target_include_directories(ncstd_iterator PRIVATE src)

target_link_libraries(ncstd_iterator PUBLIC ncstd_core)