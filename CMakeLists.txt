cmake_minimum_required(VERSION 3.21.0)
project(spo VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(GRAMMAR_RUNTIME_LIB runtime-lib)
set(TREE_VIS_LIB tree-vis-lib)
set(TREE_VIS tree-vis)
set(CFG_BUILDER cfg-builder)

add_subdirectory(src)
add_subdirectory(examples)
