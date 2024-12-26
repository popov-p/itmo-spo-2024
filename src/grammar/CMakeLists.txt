cmake_minimum_required(VERSION 3.21.0)

set(GRAMMAR_FILE V4.g)
message(STATUS "Grammar: " ${GRAMMAR_FILE})

set(ANTLR_JAR "${CMAKE_SOURCE_DIR}/antlr-3.4.jar")
message(STATUS "Detected antlr3 compiler: " ${ANTLR_JAR})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "Current binary dir: " ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "Current source dir: " ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(
    COMMAND ${Java_JAVA_EXECUTABLE} -jar ${ANTLR_JAR}
            ${CMAKE_CURRENT_SOURCE_DIR}/${GRAMMAR_FILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RESULT_VARIABLE ANTLR_EXIT_CODE
    OUTPUT_VARIABLE ANTLR_OUTPUT
    ERROR_VARIABLE ANTLR_ERROR
)

if(NOT ANTLR_EXIT_CODE EQUAL 0)
    message(FATAL_ERROR "Ошибка генерации ANTLR файлов:\n${ANTLR_ERROR}")
else()
    message(STATUS "ANTLR файлы успешно сгенерированы.")
endif()
