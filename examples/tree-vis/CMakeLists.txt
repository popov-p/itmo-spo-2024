cmake_minimum_required(VERSION 3.21.0)

add_executable(${TREE_VIS} main.c)
target_link_libraries(${TREE_VIS} ${TREE_VIS_LIB})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${TREE_VIS} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(${TREE_VIS} PRIVATE -fsanitize=address)
endif()
