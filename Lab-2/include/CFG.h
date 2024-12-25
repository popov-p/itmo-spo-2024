#ifndef BASICBLOCK_H
#define BASICBLOCK_H

#include "AST.h"
#include "LevelStack.h"
#include "ProcessedNodes.h"

enum BasicBlockType {
    standard = 0,
    merge = 1,
    loop_exit = 2,
    repeat_exit = 3
};

typedef struct {
    char **errors;
    int count;
    int capacity;
} ErrorCollection;

typedef struct BasicBlock {
    AST* node;
    enum BasicBlockType bt;
    int* successors; //sucessors` indices in BasicBlock** array
    int successorCount;
} BasicBlock;

typedef struct CFG {
    BasicBlock** blocks;
    int blockCount;
    ProcessedNodes* processedNodes;
    LoopLevelStack* loopLevelStack;
    IfLevelStack* ifLevelStack;

} CFG;

BasicBlock* createBasicBlock(AST* node, enum BasicBlockType bt);
void addSuccessor(BasicBlock* block, int successorIndex);
void addBasicBlock(CFG* cfg, BasicBlock* block);


CFG* initEmptyCFG(int processedNodesSize, int loopLevelStackSize, int ifLevelStackSize);
void freeCFG(CFG* cfg);

#endif
