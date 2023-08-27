cmake_minimum_required(VERSION 3.12)


project(ncstd_core_tests)

add_executable(ncstd_core_tests
    "test_ncstd_core.c"
)
target_include_directories(ncstd_core_tests PRIVATE ".")


include(object_library_helpers)
target_include_object_library(ncstd_core_tests PRIVATE test_common)
target_include_object_library(ncstd_core_tests PRIVATE ncstd_core)

add_test(NAME ncstd_core_tests COMMAND ncstd_core_tests)