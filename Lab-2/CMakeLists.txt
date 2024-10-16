cmake_minimum_required(VERSION 3.21.0)
project(cfgbuilder VERSION 0.1.0 LANGUAGES C)

find_library(ANTLR3_LIB antlr3c PATHS /usr/local/lib /usr/lib)

file(GLOB PROJECT_SOURCES
  src/*.h
  src/*.c
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} ${ANTLR3_LIB})
