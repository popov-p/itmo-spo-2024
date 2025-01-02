#pragma once

char* createFilePath(const char* format, ...);
char* getBaseName(const char* inputFilePath);
void executeCommand(const char* commandFormat, ...);

char* concatenateStrings(int count, const char** strings);
