#ifndef BASICBLOCK_H
#define BASICBLOCK_H

#include "AST.h"
#include "ExitStack.h"
#include "ProcessedNodes.h"

enum BasicBlockType {
    standard = 0,
    merge = 1,
    loop_exit = 2,
    repeat_exit = 3
};

typedef struct CFG {
    struct BasicBlock** blocks;
    int block_count;
    ProcessedNodes* processedNodes;
    LoopLevelCounter* loopLevelCounter;
} CFG;

typedef struct BasicBlock {
    AST* node;
    enum BasicBlockType bt;
    int* successors; //sucessors` indices in BasicBlock** array
    int successor_count;
} BasicBlock;

BasicBlock* createBasicBlock(AST* node, enum BasicBlockType bt);

void addSuccessor(BasicBlock* block, int successorIndex);

void addBasicBlock(CFG* cfg, BasicBlock* block);

void outputSubgraph(CFG* cfg,
                    int basicBlockIndex, FILE* file);

CFG* initEmptyCFG();

void freeCFG(CFG* cfg);

#endif
