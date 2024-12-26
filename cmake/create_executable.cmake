function(create_executable exec_name ${ARGN})
    add_executable(${exec_name} main.c)
    
    target_link_libraries(${exec_name} ${ARGN})

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${exec_name} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
        target_link_options(${exec_name} PRIVATE -fsanitize=address)
    endif()
endfunction()
    