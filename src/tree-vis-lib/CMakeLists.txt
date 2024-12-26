# cmake_minimum_required(VERSION 3.21.0)

# add_library(${TREE_VIS_LIB} STATIC)

# file(GLOB TREE_VIS_LIB_SOURCES
#     ${CMAKE_SOURCE_DIR}/src/tree-vis-lib/*.c
# )

# file(GLOB TREE_VIS_LIB_HEADERS
#     ${CMAKE_SOURCE_DIR}/include/tree-vis-lib/*.h
# )

# message(STATUS "TREE_VIS_LIB_CONTENTS:" ${TREE_VIS_LIB_SOURCES}
#                                         ${TREE_VIS_LIB_HEADERS})


# target_include_directories(${TREE_VIS_LIB} PUBLIC ${CMAKE_SOURCE_DIR}/include/tree-vis-lib)
# target_sources(${TREE_VIS_LIB} PRIVATE ${TREE_VIS_LIB_SOURCES})

# target_link_libraries(${TREE_VIS_LIB} ${GRAMMAR_RUNTIME_LIB})

cmake_minimum_required(VERSION 3.21.0)
create_library(${TREE_VIS_LIB} ${GRAMMAR_RUNTIME_LIB})