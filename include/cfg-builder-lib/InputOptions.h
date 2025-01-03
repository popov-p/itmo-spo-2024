#ifndef INPUTOPTIONS_H
#define INPUTOPTIONS_H

#include "AST.h"
#include "Functions.h"

void processInput(int argc, char** argv);
FL* findFunctions(AST* head, char* filename);
void findFunctionsRecursive(FL* functions, AST* node, char* filename);

#endif
