cmake_minimum_required(VERSION 3.21.0)

add_executable(${CFG_BUILDER} main.c)

target_link_libraries(${CFG_BUILDER} ${CFG_BUILDER_LIB})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${CFG_BUILDER} PRIVATE -fsanitize=address
                                                  -fno-omit-frame-pointer)
    target_link_options(${CFG_BUILDER} PRIVATE -fsanitize=address)
endif()
