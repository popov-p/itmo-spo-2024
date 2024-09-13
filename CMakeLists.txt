cmake_minimum_required(VERSION 3.5)
project(langparser VERSION 0.1.0 LANGUAGES C)

set(PROJECT_SOURCES
  src/main.c
)

add_executable(treebuilder ${PROJECT_SOURCES})
