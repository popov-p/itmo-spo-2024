function(create_library lib_name  dependencies)
    add_library(${lib_name} STATIC)

    file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/${lib_name}/*.c)
    file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/src/${lib_name}/*.h)

    message(STATUS "${lib_name} CONTENTS: \n \t ${SOURCES} \n ${HEADERS} \n")

    target_include_directories(${lib_name} PUBLIC ${CMAKE_SOURCE_DIR}/include/${lib_name})
    target_sources(${lib_name} PRIVATE ${SOURCES})

    target_link_libraries(${lib_name} ${dependencies})
endfunction()