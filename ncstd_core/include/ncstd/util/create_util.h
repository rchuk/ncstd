#pragma once

/**
 * @file
*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ncstd/memory.h"


/** \addtogroup create_util
 *  @brief Object creation utilities
 *  @{
*/

/**
 * @brief Creates an object on the heap
 * 
 * Dynamically allocates memory with malloc, and then copies data
 * pointed to by @p self_init with specified size.
 * 
 * @param self_init struct initialization data
 * @param size struct size
 * 
 * @return pointer to allocated memory containing initialized object
*/
inline void* nc_util_create_with(void* self_init, size_t size) {
    void* const self = nc_malloc(size);

    memcpy(self, self_init, size);

    return self;
}

/**
 * @brief Creates an object with flexible array of bytes member on the heap
 * 
 * Dynamically allocates memory with malloc, and then copies data
 * pointed to by @p self_init and @p flexible_init with specified sizes.
 * 
 * ## Example
 * @code
 *  typedef struct {
 *      int32_t data;
 *      uint8_t flex[];
 *  } Foo;
 * 
 *  typedef struct {
 *      int32_t number; 
 *  } Bar;
 * 
 *  typedef struct {
 *      int64_t number1;
 *      int64_t number2;
 *  } Baz;
 * 
 *  ...
 *  
 *  Foo* const foo = nc_util_create_with_flexible(
 *      &(Foo) { .data = 69 },
 *      sizeof(Foo),
 *      &(Bar) { .number = 420 },
 *      sizeof(Bar)
 *  );
 * 
 *  Foo* const other_foo = nc_util_create_with_flexible(
 *      &(Foo) { .data = 69 },
 *      sizeof(Foo),
 *      &(Baz) { .number1 = 666, .number2 = 777 },
 *      sizeof(Baz)
 *  );
 * 
 *  ...
 * @endcode
 * 
 * @param self_init struct initialization data
 * @param size struct size
 * @param flexible_init flexible struct initialization data
 * @param flexible_size flexible struct size
 * 
 * @return pointer to allocated memory containing initialized object
*/
inline void* nc_util_create_with_flexible(void* self_init, size_t size, void* flexible_init, size_t flexible_size) {
    void* const self = nc_malloc(size + flexible_size);

    memcpy(self, self_init, size);
    memcpy((uint8_t*)self + size, flexible_init, flexible_size);

    return self;
}

/**
 * @}
*/