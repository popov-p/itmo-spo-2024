#ifndef INPUTOPTIONS_H
#define INPUTOPTIONS_H

#include "AST.h"
#include "Functions.h"

void processInput(int argc, char** argv);
FunctionList* findFunctions(AST* head, char* filename);
void findFunctionsRecursive(FunctionList* functions, AST* node, char* filename);

#endif
