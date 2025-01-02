#pragma once
#include <stdio.h>

char* createFilePath(const char* format, ...);
char* getBaseName(const char* inputFilePath);
void executeCommand(const char* commandFormat, ...);

char* concatenateStrings(int count, const char** strings);

FILE* open_file(const char* filename, const char* mode);

void close_file(FILE* file);
