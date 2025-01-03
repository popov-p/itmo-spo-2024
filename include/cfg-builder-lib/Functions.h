#pragma once

#include "AST.h"
#include "CFG.h"
#include "ST.h"

typedef struct F { // Function
    char* name;
    AST* signature;
    CFG* cfg;
    ST* symbolTable;
    char* sourceFile;
} F;

typedef struct FL { // Function List
    F** functions;
    int count;
} FL;

F* F_Create(const char* name,
                        AST* signature,
                        CFG* cfg,
                        ST* symbolTable,
                        const char* sourceFile);
void F_Free(F* func);

FL* FL_Create();
void FL_Free(FL* list);
void FL_AddF(FL* list, F* func);
int FL_FExists(FL* functionList, char* funcName);

FL* FL_FindFsInAST(AST* head, char* filename); /* wrapper */
void FL_FindFInAST(FL* functions, AST* node, char* filename);
