cmake_minimum_required(VERSION 3.12)


project(ncstd_core)


add_library(ncstd_core OBJECT
    "include/ncstd/containers/unsafe/raw_buffer.h"
    "include/ncstd/macros/option_macros.h"
    "include/ncstd/util/create_util.h"
    "include/ncstd/util/panic_handlers.h"
    "include/ncstd/memory.h"

    "src/containers/unsafe/raw_buffer.c"
    "src/util/create_util.c"
    "src/util/panic_handlers.c"
    "src/memory.c"
)

target_include_directories(ncstd_core PUBLIC include)
target_include_directories(ncstd_core PRIVATE include/ncstd)
target_include_directories(ncstd_core PRIVATE src)

target_compile_features(ncstd_core PUBLIC c_std_11)

if (NCSTD_ENABLE_TESTS)
    add_subdirectory(tests)
endif()