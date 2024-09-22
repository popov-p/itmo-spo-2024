cmake_minimum_required(VERSION 3.5)
project(langparser VERSION 0.1.0 LANGUAGES C)

find_library(ANTLR3_LIB antlr3c PATHS /usr/local/lib /usr/lib)

set(PROJECT_SOURCES
  src/Var4Lexer.c
  src/Var4Lexer.h
  src/Var4Parser.c
  src/Var4Parser.h
  src/main.c
)

add_executable(treebuilder ${PROJECT_SOURCES})
target_link_libraries(treebuilder ${ANTLR3_LIB})


