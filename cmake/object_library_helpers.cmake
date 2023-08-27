

macro(target_use_object_library_sources target access library)
    target_sources(${target} ${access} $<TARGET_OBJECTS:${library}>)
endmacro()

macro(target_include_object_library target access library)
    target_use_object_library_sources(${target} ${access} ${library})
    target_link_libraries(${target} ${access} ${library})
endmacro()
