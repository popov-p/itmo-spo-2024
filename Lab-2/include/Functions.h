#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "AST.h"
#include "CFG.h"

typedef struct Function {
    char* name;
    AST* signature;
    CFG* cfg;
    char* sourceFile;
} Function;

typedef struct {
    Function** items;
    int count;
} FunctionList;

Function* createFunction(const char* name,
                         AST* signature,
                         CFG* cfg,
                         const char* sourceFile);
FunctionList* createFunctionList();
void freeFunctionList(FunctionList* list);
void freeFunction(Function* func);
void addFunction(FunctionList* list, Function* func);
int functionExists(FunctionList* functions, char* funcName);
#endif
