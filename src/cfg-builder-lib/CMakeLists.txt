cmake_minimum_required(VERSION 3.21.0)

# add_library(${CFG_BUILDER_LIB} STATIC)

# file(GLOB CFG_BUILDER_LIB_SOURCES
#     ${CMAKE_SOURCE_DIR}/src/cfg-builder-lib/*.c
# )

# file(GLOB TREE_VIS_LIB_HEADERS
#     ${CMAKE_SOURCE_DIR}/include/cfg-builder-lib/*.h
# )

# message(STATUS "CFG_BUILDER_LIB_CONTENTS:" ${CFG_BUILDER_LIB_SOURCES}
#                                            ${CFG_BUILDER_LIB_HEADERS})

# target_include_directories(${CFG_BUILDER_LIB} PUBLIC ${CMAKE_SOURCE_DIR}/include/cfg-builder-lib)
# target_sources(${CFG_BUILDER_LIB} PRIVATE ${CFG_BUILDER_LIB_SOURCES})

# target_link_libraries(${CFG_BUILDER_LIB} ${TREE_VIS_LIB})

create_library(${CFG_BUILDER_LIB} "${TREE_VIS_LIB}")