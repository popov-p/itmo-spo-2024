cmake_minimum_required(VERSION 3.5)
project(langparser VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")

set(ANTLR_INCLUDE_DIRS /usr/local/include)
set(ANTLR_LIBRARIES /usr/local/lib/libantlr3c.a)


add_definitions(-DANTLR3_DEBUG)

include_directories(${ANTLR_INCLUDE_DIRS})
link_directories(/usr/local/lib)

set(PROJECT_SOURCES
  src/Var4Lexer.c
  src/Var4Lexer.h
  src/Var4Parser.c
  src/Var4Parser.h
  src/main.c
)

add_executable(treebuilder ${PROJECT_SOURCES})
target_link_libraries(treebuilder ${ANTLR3C_PATH})


