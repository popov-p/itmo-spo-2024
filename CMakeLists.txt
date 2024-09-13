cmake_minimum_required(VERSION 3.5)
project(langparser VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")

set(ANTLR_INCLUDE_DIRS /usr/local/include)
set(ANTLR_LIBRARIES /usr/local/lib/libantlr3c.a)



include_directories(${ANTLR_INCLUDE_DIRS})
link_directories(/usr/local/lib)

set(PROJECT_SOURCES
  src/TLexer.c
  src/TLexer.h
  src/TParser.c
  src/TParser.h
  src/main.c
)

add_executable(treebuilder ${PROJECT_SOURCES})
target_link_libraries(treebuilder antlr3c)


