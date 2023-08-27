#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * @file
*/

/** \addtogroup memory
 *  @brief Memory management utilities
 *  @{
*/

/**
 * @brief Allocates size bytes of uninitialized storage using stdlib malloc.
 * 
 * # Safety
 * If @p size is 0, the behaviour is implementation-defined.
 * 
 * @note Handles out of memory error using @ref nc_handle_out_of_memory(),
 * that might or might not ever return.
 * 
 * @param size number of bytes to allocate
 * 
 * @return pointer to the beginning of newly allocated memory.
 * On failure returns a null pointer if error handler ever returns
*/
void* nc_malloc(size_t size);
/**
 * @brief Allocates memory for an array of @p count objects of @p object_size and initializes all bytes in the
 * allocated storage to zero using stdlib calloc
 * 
 * # Safety
 * If @p size or @p object_size is 0, the behaviour is implementation-defined.
 * 
 * @note Handles out of memory error using @ref nc_handle_out_of_memory(),
 * that might or might not ever return.
 * 
 * @param count number of objects to allocate
 * @param object_size size of each object
 * 
 * @return pointer to the beginning of newly allocated memory.
 * On failure returns a null pointer if error handler ever returns
*/
void* nc_calloc(size_t count, size_t object_size);
/**
 * @brief Reallocates the given area of memory using stdlib realloc
 * 
 * On success, function returns pointer to newly allocated memory.
 * On failure, returns @p NULL and passed pointer is freed.
 * For preserving old pointer look at @ref nc_realloc_preserving()
 * 
 * If @p ptr is @p NULL, the behavior is the same as calling @ref nc_malloc().
 * 
 * # Safety
 * If @p new_size is 0 or @p ptr doesn't point to allocated memory
 * the behaviour is undefined.
 * 
 * @note Handles out of memory error using @ref nc_handle_out_of_memory(),
 * that might or might not ever return.
 * 
 * @param[in, out] ptr pointer to the allocated memory
 * @param new_size new size of the allocated memory in bytes 
 * 
 * @return pointer to the beginning of newly allocated memory.
 * On failure returns a null pointer if error handler ever returns
*/
void* nc_realloc(void* ptr, size_t new_size);
/**
 * @brief Reallocates the given area of memory using stdlib realloc
 * 
 * Function returns whether area was reallocated with the new size.
 * On success, it ovewrites the pointer with the new address.
 * On failure, passed pointer stays valid with all the data.
 * 
 * # Safety
 * If @p in_out_ptr is @p NULL or variable pointed to by it doesn't point to
 * allocated memory the behaviour is undefined.
 * If @p new_size is 0, the behaviour is undefined.
 * 
 * @note Handles out of memory error using @ref nc_handle_out_of_memory(),
 * that might or might not ever return.
 * 
 * @param[in, out] in_out_ptr pointer to variable that stores memory pointer 
 * @param new_size new size of the allocated memory in bytes 
 * 
 * @return whether reallocation was successful
*/
bool nc_realloc_preserving(void** in_out_ptr, size_t new_size);

/**
 * @brief Deallocates the space previously allocated by the functions in this module using stdlib free.
 * 
 * The function accepts (and does nothing with) the @p NULL pointer.
 * 
 * @param ptr pointer to the memory to deallocate
*/
void nc_free(void* ptr);

/**
 * @}
*/