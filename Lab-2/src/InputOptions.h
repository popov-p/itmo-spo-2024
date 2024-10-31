#ifndef INPUTOPTIONS_H
#define INPUTOPTIONS_H

#include "AST.h"
#include "BasicBlock.h"

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

void processInput(int argc, char** argv);
FunctionList* findFunctions(AST* head, char* filename);
void findFunctionsRecursive(FunctionList* functions, AST* node, char* filename);

void addFunction(FunctionList* list, Function* func);
Function* createFunction(const char* name, AST* signature, CFG* cfg, const char* sourceFile);

#endif
