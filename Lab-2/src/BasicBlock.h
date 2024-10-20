#ifndef BASICBLOCK_H
#define BASICBLOCK_H

#include "AST.h"

typedef struct CFG {
    struct BasicBlock** blocks;
    int block_count;
} CFG;

typedef struct BasicBlock {
    AST* node;
    int* successors; //sucessors` indices in BasicBlock** array
    int successor_count;
} BasicBlock;

BasicBlock* createBasicBlock(AST* node);

void addSuccessor(BasicBlock* block, int successorIndex);

void addBasicBlock(CFG* cfg, BasicBlock* block);

void outputSubgraph(CFG* cfg,
                    int basicBlockIndex, FILE* file);

CFG* initEmptyCFG();

void freeCFG(CFG* cfg);

#endif
