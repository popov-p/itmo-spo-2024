#pragma once

char* createFilePath(const char* format, ...);
char* getBaseName(const char* inputFilePath);
void executeCommand(const char* errorMessage, const char* commandFormat, ...);
