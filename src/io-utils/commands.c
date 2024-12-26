#include "commands.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* createFilePath(const char* format, ...) {
    va_list args;
    va_start(args, format);
    size_t len = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);

    char* filePath = (char*)malloc(len);
    if (!filePath) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    va_start(args, format);
    vsnprintf(filePath, len, format, args);
    va_end(args);

    return filePath;
}


char* getBaseName(const char* inputFilePath) {
    const char* fileName = strrchr(inputFilePath, '/');
    fileName = (fileName) ? fileName + 1 : inputFilePath;

    char* baseName = strdup(fileName);
    if (!baseName) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    char* dot = strrchr(baseName, '.');
    if (dot) {
        *dot = '\0';
    }

    return baseName;
}

void executeCommand(const char* commandFormat, ...) {
    va_list args;
    va_start(args, commandFormat);

    size_t commandLen = vsnprintf(NULL, 0, commandFormat, args) + 1;
    va_end(args);

    char* command = (char*)malloc(commandLen);
    if (!command) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    va_start(args, commandFormat);
    vsnprintf(command, commandLen, commandFormat, args);
    va_end(args);

    printf("Executing command: %s\n", command);

    int result = system(command);

    if (result != 0)
        fprintf(stderr, "Error occurred. Result code: %d\n", result);
    else
        printf("Command executed successfully.\n");

    free(command);

    return;
}
