#pragma once

/**
 * @file
*/

/** \addtogroup panic_handlers
 *  @brief Panic handlers
 *  @{
*/

#ifdef NC_DOXYGEN
/**
 * @brief Macro enabling custom handling of out of memory error
 * 
 * You should define this macro and provide
 * @code
 *  void nc_user_handle_out_of_memory()
 * @endcode
 * function that's going to be called when one of the allocation routine fails.
*/
#define NC_USER_HANDLE_OUT_OF_MEMORY
#endif

/**
 * @brief Default function that handles out of memory error.
 * Current behaviour is calling stdlib abort.
*/
void nc_default_handle_out_of_memory();

/**
 * @brief Handles out of memory error
 * 
 * If @ref NC_USER_HANDLE_OUT_OF_MEMORY macro is defined,
 * nc_user_handle_out_of_memory() function is going to be called.
 * Otherwise, @ref nc_default_handle_out_of_memory() function is called.
*/
void nc_handle_out_of_memory();

/**
 * @}
*/