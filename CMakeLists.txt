cmake_minimum_required(VERSION 3.21.0)
project(spo VERSION 0.1.0 LANGUAGES C)

include(${CMAKE_SOURCE_DIR}/cmake/create_library.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/create_executable.cmake)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(SRCDIR src)
set(EXAMPLEDIR examples)

set(GRAMMAR grammar)
set(GRAMMAR_RUNTIME_LIB runtime-lib)

set(TREE_VIS_LIB tree-vis-lib)
set(TREE_VIS tree-vis)

set(CFG_BUILDER_LIB cfg-builder-lib)
set(CFG_BUILDER cfg-builder)

set(IO_UTILS io-utils)
set(SAFE_MEM safe-mem)

set(ASM_GEN asm-gen)
set(ASM_GEN_LIB asm-gen-lib)

add_subdirectory(${SRCDIR}/${GRAMMAR})
add_subdirectory(${SRCDIR}/${TREE_VIS_LIB})
add_subdirectory(${SRCDIR}/${CFG_BUILDER_LIB})
add_subdirectory(${SRCDIR}/${ASM_GEN_LIB})

add_subdirectory(${SRCDIR}/${IO_UTILS})
add_subdirectory(${SRCDIR}/${SAFE_MEM})

add_subdirectory(${EXAMPLEDIR}/${TREE_VIS})
add_subdirectory(${EXAMPLEDIR}/${CFG_BUILDER})
add_subdirectory(${EXAMPLEDIR}/${ASM_GEN})
