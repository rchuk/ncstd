cmake_minimum_required(VERSION 3.12)


project(ncstd_exec_test)

add_executable(ncstd_exec_test
    "src/main.c"
)

target_link_libraries(ncstd_exec_test ncstd_static)