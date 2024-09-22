cmake_minimum_required(VERSION 3.5)
project(langparser VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
find_library(ANTLR3_LIB antlr3c PATHS /usr/local/lib /usr/lib)

set(PROJECT_SOURCES
  src/Var4PrevLexer.c
  src/Var4PrevLexer.h
  src/Var4PrevParser.c
  src/Var4PrevParser.h
  src/main.c
)

add_executable(treebuilder ${PROJECT_SOURCES})
target_link_libraries(treebuilder ${ANTLR3_LIB})


