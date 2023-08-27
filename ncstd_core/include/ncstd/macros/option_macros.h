#pragma once

/**
 * @file
*/

#include <stdbool.h>

/** \addtogroup option_macros
 *  @brief Various macros for working with option types
 *  @{
*/

/**
 * @brief Macro that defines name of an optional type
 * 
 * ## Example
 * @code
 *  NC_Option(char32_t)
 * @endcode
 * expands to
 * @code
 *  NC_Option_char32_t
 * @endcode
 * 
 * @param type type that is wrapped into option 
*/
#define NC_OPTION(type) NC_Option_##type

#define NC_INTERNAL_OPTION_FUNCTION_NAME(type_snake_case, function_name) nc_option_##type_snake_case##_##function_name

/**
 * @brief Macro that defines a simple optional type that uses a boolean flag
 * 
 * ## Generated code example
 * ### Input
 * @code
 *  typedef struct {
 *      int32 some_value;
 *  } Foo;
 * 
 *  NC_DEFINE_OPTION(Foo, foo);
 * @endcode
 * ### Generated code
 * (Only basic functions are shown)
 * @code
 *  typedef struct {
 *      Foo value;
 *      bool is_some;
 *  } NC_Option_Foo;
 *   
 *  inline NC_Option_Foo nc_option_foo_init_some(Foo value) {
 *      return (NC_Option_Foo) { .value = value, .is_some = true };
 *  }
 *    
 *  inline NC_Option_Foo nc_option_foo_init_none() {
 *      return (NC_Option_Foo) { .is_some = false };
 *  }
 * 
 *  inline Foo nc_option_foo_value_or(NC_Option_Foo self, Foo default_value) {
 *      if (!self.is_some)
 *          return default_value;
 *         
 *      return self.value;
 *  }
 * @endcode
 * 
 * If the type can represent none state internally, implementation can be created manually.
 * It is your responsibility to avoid creating object in an invalid state.
 * ## Example
 * @code
 *  typedef struct {
 *      void* ptr; 
 *  } Pointer;
 * 
 *  typedef struct {
 *      Pointer value;
 *  } NC_OPTION(Pointer);
 *
 *  bool nc_option_pointer_is_some(NC_OPTION(Pointer) self) {
 *      return self.ptr;
 *  }
 *
 *  NC_OPTION(Pointer) nc_option_pointer_init_some(Pointer pointer) {
 *      return (NC_OPTION(Pointer)) { .value = pointer };
 *  }
 *
 *  NC_OPTION(Pointer) nc_option_pointer_init_none() {
 *      return (NC_OPTION(Pointer)) { .value = { .ptr = NULL } };
 *  }
 * @endcode
 * 
 */
#define NC_DEFINE_OPTION(type, type_snake_case)                                                                         \
    /**
        @brief Struct that represents an optional value of type
        
        @details Using this struct, value might be present or not. State should be checked with @p is_some member.
        Then in case it's present, object can be retrieved from @p value member.
    */                                                                                                                  \
    typedef struct {                                                                                                    \
        /** Contained object (or some unspecified data, in case option doesn't contain a value) */                      \
        type value;                                                                                                     \
        /** Flag signifying whether option contains a value */                                                                                                                \
        bool is_some;                                                                                                   \
    } NC_OPTION(type);                                                                                                  \
                                                                                                                        \
    /**
        @memberof NC_Option_##type
    
        @brief Initializes an option with given @p value object
    
        @param value object
    
        @return option containing given object                                                                                       
    */                                                                                                                  \
    inline NC_OPTION(type) NC_INTERNAL_OPTION_FUNCTION_NAME(type_snake_case, init_some)(type value) {                   \
        return (NC_OPTION(type)) { .value = value, .is_some = true };                                                   \
    }                                                                                                                   \
                                                                                                                        \
    /**
        @memberof NC_Option_##type
     
        @brief Initializes an option containing no value
     
        @return option containing no value
    */                                                                                                                  \
    inline NC_OPTION(type) NC_INTERNAL_OPTION_FUNCTION_NAME(type_snake_case, init_none)() {                             \
        return (NC_OPTION(type)) { .is_some = false };                                                                  \
    }                                                                                                                   \
                                                                                                                        \
    /**
        @memberof NC_Option_##type
     
        @brief Returns the contained value or provided default value
    
        @param default_value default value that will be returned if option contains no value
    
        @return contained value if option is @p is_some member is true or @p default_value otherwise
    */                                                                                                                  \
    inline type NC_INTERNAL_OPTION_FUNCTION_NAME(type_snake_case, value_or)(NC_OPTION(type) self, type default_value) { \
        if (!self.is_some)                                                                                              \
            return default_value;                                                                                       \
                                                                                                                        \
        return self.value;                                                                                              \
    }

    // TODO(@rchuk): Add more helper functions

/**
 *  @}
*/
