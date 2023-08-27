cmake_minimum_required(VERSION 3.12)


project(test_common)

add_library(test_common OBJECT
    "src/test_common.c"
)
target_include_directories(test_common PUBLIC include)

target_link_libraries(test_common PUBLIC cmocka::cmocka)