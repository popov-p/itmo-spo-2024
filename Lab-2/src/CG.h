#ifndef CG_H
#define CG_H

#include "AST.h"
#include "Functions.h"

typedef struct CGB { // call graph block
    AST* node;
    int* successors; //sucessors` indices in CGB2** array
    int successorCount;
} CGB;

typedef struct CG
{
    CGB** blocks;
    int blockCount;
} CG;

CG* initEmptyCG(FunctionList* declaredFunctions);

CGB* createCallGraphBlock(AST* node);
void addCallGraphBlock(CG* cg, CGB* block);

void cgWalker(CG* cg, AST* current, int* lastBlockIndex);
int cgWalkerLinkWithParent(CG* cg, AST* current, int* lastBlockIndex);
CG* generateCG(AST* head, FunctionList* declaredFunctions);
#endif
