#pragma once

/**
 * @file
*/

#include <stddef.h>
#include <stdint.h>


/** \addtogroup unsafe_containers
 *  @brief Unsafe containers
 *  @{
*/

/**
 * @brief Structure providing capabilities to allocate, reallocate and deallocate
 * memory on the heap for storing multiple objects of the same type.
 * 
 * It's meant to be used as a base for creating different types of collections
 * such as vector, hash map, etc. 
*/
typedef struct {
    /**
     * @protected
     * 
     * @brief Members are not stable, and are displayed for educational purposes only
    */
    struct {
        /** @protected Pointer to the start of the buffer */
        uint8_t* data;
        /** @protected Capacity of the raw buffer */
        size_t capacity;
    } p;
} NC_RawBuffer;

/**
 * @memberof NC_RawBuffer
 * 
 * @brief Initializes empty raw buffer (performs no dynamic allocations)
 * 
 * @note Calling this function with @p object_size equal to 0, doesn't invoke
 * undefined behaviour per se, but according to contract, that object size must
 * be persistent between all function calls on this buffer, it is illegal.
 * 
 * @param object_size size of a single object, must be persistent between all function calls
 * on this buffer
 * 
 * @return created raw buffer
*/
NC_RawBuffer nc_raw_buffer_init(size_t object_size);
/**
 * @memberof NC_RawBuffer
 * 
 * @brief Initalizes raw buffer with specified capacity and object size
 * 
 * ## Safety
 * Calling this function with @p object_size equal to 0, leads to undefined behaviour
 * 
 * @param capacity starting capacity of the buffer
 * @param object_size size of a single object, must be persistent between all function calls
 * on this buffer
 * 
 * @return created raw buffer
*/
NC_RawBuffer nc_raw_buffer_init_with_capacity(size_t capacity, size_t object_size);
/**
 * @memberof NC_RawBuffer
 * 
 * @brief Intializes fraw buffer with specified object size, capacity equal to @p count and
 * copies all objects to the buffer.
 * 
 * ## Safety
 * Calling this function with @p object_size equal to 0, leads to undefined behaviour.
 * @p objects can't be @p NULL and must point to allocated memory with @p count objects of size @p object_size.
 * 
 * @param objects pointer to objects
 * @param count object count
 * @param object_size size of a single object, must be persistent between all calls
 * to this buffer
 * 
 * @return created raw buffer
*/
NC_RawBuffer nc_raw_buffer_init_with_objects(const void* objects, size_t count, size_t object_size);
/**
 * @memberof NC_RawBuffer
 * 
 * @brief Destroys the raw buffer by freeing all memory allocated by it
*/
void nc_raw_buffer_free(NC_RawBuffer* self);

/**
 * @memberof NC_RawBuffer
 * 
 * @brief Returns pointer to raw buffer data
 * 
 * @return pointer to raw buffer data
*/
void* nc_raw_buffer_data(const NC_RawBuffer* self);
/**
 * @memberof NC_RawBuffer
 * 
 * @brief Returns capacity of the raw buffer
 * 
 * @return capacity of the raw buffer
*/
size_t nc_raw_buffer_capacity(const NC_RawBuffer* self);

/**
 * @memberof NC_RawBuffer
 * 
 * @brief Returns pointer to object at specified @p index
 * 
 * @param index object index
 * @param object_size object size, persisent between all function calls on this buffer
 * 
 * @return pointer to object or @p NULL if the index is out of bounds
*/
void* nc_raw_buffer_get(const NC_RawBuffer* self, size_t index, size_t object_size);
/**
 * @memberof NC_RawBuffer
 * 
 * @brief Returns pointer to object at specified @p index
 * without performing bounds checking
 * 
 * ## Safety
 * Calling function with @p index out of bounds leads to undefined behaviour.
 * 
 * @param index object index
 * @param object_size object size, persisent between all function calls on this buffer
 * 
 * @return pointer to object
*/
void* nc_raw_buffer_get_unchecked(const NC_RawBuffer* self, size_t index, size_t object_size);
/**
 * @memberof NC_RawBuffer
 * 
 * @brief Returns pointer to @p count objects, starting at specified @p index
 * 
 * @param index start object index
 * @param count objects count
 * @param object_size object size, persisent between all function calls on this buffer
 * 
 * @return pointer to objects or @p NULL when performing access out of bounds
*/
void* nc_raw_buffer_get_multiple(const NC_RawBuffer* self, size_t index, size_t count, size_t object_size);
/**
 * @memberof NC_RawBuffer
 * 
 * @brief Returns pointer to @p count objects, starting at specified @p index
 * without performing bounds checking
 * 
 * ## Safety
 * Calling function with @p index and @p count out of bounds leads to undefined behaviour.
 * 
 * @param index start object index
 * @param count objects count
 * @param object_size object size, persisent between all function calls on this buffer
 * 
 * @return pointer to objects or @p NULL when performing access out of bounds
*/
void* nc_raw_buffer_get_multiple_unchecked(const NC_RawBuffer* self, size_t index, size_t count, size_t object_size);

/**
 * @memberof NC_RawBuffer
 * 
 * @brief Sets new value for object at specified @p index
 * 
 * If the @p index is out of bounds, function silently returns.
 * 
 * @param object pointer to new object data
 * @param index object index
 * @param object_size object size, persisent between all function calls on this buffer
*/
void nc_raw_buffer_set(NC_RawBuffer* self, const void* object, size_t index, size_t object_size);
/**
 * @memberof NC_RawBuffer
 * 
 * @brief Sets new value for object at specified @p index
 * 
 * ## Safety
 * If the @p index is out of bounds, the behaviour is undefined.
 * 
 * @param object pointer to new object data
 * @param index object index
 * @param object_size object size, persisent between all function calls on this buffer
*/
void nc_raw_buffer_set_unchecked(NC_RawBuffer* self, const void* object, size_t index, size_t object_size);
/**
 * @memberof NC_RawBuffer
 * 
 * @brief Sets new values for @p count objects, starting at specified @p index
 * 
 * If the @p index or @p count is out of bounds, function silently returns.
 * 
 * @param objects pointer to new objects data
 * @param index start objects index
 * @param count objects count
 * @param object_size object size, persisent between all function calls on this buffer
*/
void nc_raw_buffer_set_multiple(NC_RawBuffer* self, const void* objects, size_t index, size_t count, size_t object_size);
/**
 * @memberof NC_RawBuffer
 * 
 * @brief Sets new values for @p count objects, starting at specified @p index
 * 
 * ## Safety
 * If the @p index or @p count is out of bounds, the behaviour is undefined
 * 
 * @param objects pointer to new objects data
 * @param index start objects index
 * @param count objects count
 * @param object_size object size, persisent between all function calls on this buffer
*/
void nc_raw_buffer_set_multiple_unchecked(NC_RawBuffer* self, const void* objects, size_t index, size_t count, size_t object_size);

/**
 * @memberof NC_RawBuffer
 * 
 * @brief Resizes the buffer, expanding or shrinking it to @p new_capacity
 * 
 * ## Safety
 * If the @p new_capacity or @p object_size is 0, the behaviour is undefined
 * 
 * @param objects pointer to new objects data
 * @param index start objects index
 * @param object_size object size, persisent between all function calls on this buffer
*/
void nc_raw_buffer_resize_unchecked(NC_RawBuffer* self, size_t new_capacity, size_t object_size);

// TODO
void nc_raw_buffer_grow_amorthized(NC_RawBuffer* self, size_t required_capacity, size_t growth_factor, size_t object_size);

/**
 * @}
*/
