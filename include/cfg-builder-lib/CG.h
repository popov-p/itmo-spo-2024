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

CG* initEmptyCG();

CGB* createCallGraphBlock(AST* node);
void addCallGraphBlock(CG* cg, CGB* block);

int findIndexByName(FunctionList* declaredFunctions, AST* name);
CG* generateCG(FunctionList* declaredFunctions);
void freeCG(CG* cg);
void outputCG(CG* cg, FILE* file);
void outputCgNodes(CG* cg, FILE* file);
void outputCgEdges(CG* cg, FILE* file);
#endif
