function(create_executable exec_name)
    add_executable(${exec_name} main.c)
    
    target_link_libraries(${exec_name} PRIVATE ${ARGN})
    target_compile_options(${exec_name} PRIVATE
        $<$<AND:$<CONFIG:Debug>,$<BOOL:${USE_SANITIZERS}>>:-fsanitize=address -fno-omit-frame-pointer>
    )

    target_link_options(${exec_name} PRIVATE
        $<$<AND:$<CONFIG:Debug>,$<BOOL:${USE_SANITIZERS}>>:-fsanitize=address>
    )
endfunction()
