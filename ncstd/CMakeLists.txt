cmake_minimum_required(VERSION 3.12)


project(ncstd)


add_library(ncstd OBJECT
    "src/ncstd.c"
)

target_include_directories(ncstd PUBLIC include)
target_include_directories(ncstd PRIVATE include/ncstd)
target_include_directories(ncstd PRIVATE src)


include(object_library_helpers)

target_include_object_library(ncstd PUBLIC ncstd_core)

if (NCSTD_FEATURE_ENABLE_ITERATOR)
    target_include_object_library(ncstd PUBLIC ncstd_iterator)
endif()
if (NCSTD_FEATURE_ENABLE_STRING)
    target_include_object_library(ncstd PUBLIC ncstd_string)
endif()


if (NCSTD_BUILD_STATIC)
    add_library(ncstd_static STATIC)
    target_link_libraries(ncstd_static ncstd)
endif()

if (NCSTD_BUILD_SHARED)
    add_library(ncstd_shared SHARED)
    target_link_libraries(ncstd_shared ncstd)
endif()