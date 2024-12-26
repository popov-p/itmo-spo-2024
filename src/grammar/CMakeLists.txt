cmake_minimum_required(VERSION 3.21.0)

find_package(Java REQUIRED)
set(GRAMMAR_FILE ${CMAKE_CURRENT_SOURCE_DIR}/V4.g)
message(STATUS "Grammar: ${GRAMMAR_FILE}")

set(ANTLR_JAR "${CMAKE_SOURCE_DIR}/antlr-3.4.jar")
message(STATUS "Detected antlr3 compiler: " ${ANTLR_JAR})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "Current binary dir: " ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "Current source dir: " ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "Found java executable: " ${Java_JAVA_EXECUTABLE})

execute_process(
    COMMAND ${Java_JAVA_EXECUTABLE} -jar ${ANTLR_JAR}
            ${GRAMMAR_FILE}
            -o ${CMAKE_CURRENT_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RESULT_VARIABLE ANTLR_EXIT_CODE
    OUTPUT_VARIABLE ANTLR_OUTPUT
    ERROR_VARIABLE ANTLR_ERROR
)

set(ANTLR_COMPILER_OUTPUT ANTLR_EXIT_CODE ANTLR_OUTPUT ANTLR_ERROR)

foreach(OUTPUT ${ANTLR_COMPILER_OUTPUT})
    if(DEFINED ${OUTPUT} AND NOT ${OUTPUT} STREQUAL "")
        if(${OUTPUT} STREQUAL ANTLR_ERROR)
            message(FATAL_ERROR "${OUTPUT}: ${${OUTPUT}}")
        else()
            message(STATUS "${OUTPUT}: ${${OUTPUT}}")
        endif()
    endif()
endforeach()

if(NOT ANTLR_EXIT_CODE EQUAL 0)
    message(STATUS "Ошибка генерации ANTLR файлов.")
else()
    message(STATUS "ANTLR файлы успешно сгенерированы.")
endif()
