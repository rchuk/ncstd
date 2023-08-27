cmake_minimum_required(VERSION 3.12)


project(ncstd_project C)

# Configuration
option(NCSTD_ENABLE_TESTS "Enable testing (requires CMocka installed)" ON)

option(NCSTD_BUILD_STATIC "Enable building static library" ON)
option(NCSTD_BUILD_SHARED "Enable building shared library" ON)

option(NCSTD_FEATURE_ENABLE_ITERATOR "Enable iterator feature" ON)
option(NCSTD_FEATURE_ENABLE_STRING "Enable string feature" ON)
 

# Add include path for modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Configure compiler parameters
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if (NCSTD_BUILD_SHARED)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Add definitions for library features
if (NCSTD_FEATURE_ENABLE_ITERATOR)
    add_definitions(-DNC_FEATURE_ITERATOR)
endif()

if (NCSTD_FEATURE_ENABLE_STRING)
    add_definitions(-DNC_FEATURE_STRING)
endif()

# Enable testing
if (NCSTD_ENABLE_TESTS)
    find_package(CMocka)
    if (NOT ${CMOCKA_FOUND})
        message(FATAL_ERROR "Testing the library requires CMocka to be installed")
    endif()

    add_subdirectory(test_common)

    enable_testing()
endif()

# Add documentation target
find_package(Doxygen)
if (${DOXYGEN_FOUND})
    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
else()
    message("Doxygen needs to be installed to generate documentation")
endif()


# Add modules

# Core modules
add_subdirectory(ncstd_core)

# Optional modules
if (NCSTD_FEATURE_ENABLE_ITERATOR)
    message(STATUS "Enabling iterator feature")

    add_subdirectory(ncstd_iterator)
endif()
if (NCSTD_FEATURE_ENABLE_STRING)
    message(STATUS "Enabling string feature")

    add_subdirectory(ncstd_string)
endif()

# Main library module
add_subdirectory(ncstd)

#
add_subdirectory(ncstd_exec_test)
#