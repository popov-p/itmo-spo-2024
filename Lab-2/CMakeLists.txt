cmake_minimum_required(VERSION 3.21.0)
project(cfgbuilder VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER "clang")
if (CMAKE_C_COMPILER_ID STREQUAL "clang")
    add_compile_options(-Wno-insecureAPI)
endif()

 find_library(ANTLR3_LIB antlr3c PATHS /usr/local/lib /usr/lib)

file(GLOB PROJECT_HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} ${ANTLR3_LIB})
