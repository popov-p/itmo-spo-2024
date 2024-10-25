cmake_minimum_required(VERSION 3.21.0)
project(cfgbuilder VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER "clang")
if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wno-insecureAPI)
endif()

find_library(ANTLR3_LIB antlr3c PATHS /usr/local/lib /usr/lib)

file(GLOB PROJECT_SOURCES
  src/*.h
  src/*.c
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} ${ANTLR3_LIB})
