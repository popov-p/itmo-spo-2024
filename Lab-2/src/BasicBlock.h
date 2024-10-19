#ifndef BASICBLOCK_H
#define BASICBLOCK_H

#include <stdint.h>

typedef struct CFG {
    struct BasicBlock** blocks;
    int block_count;
} CFG;

typedef struct BasicBlock {
    uint32_t id;
    int* successors; //sucessors` indices in BasicBlock** array
    int successor_count;
} BasicBlock;

BasicBlock* createBasicBlock(uint32_t id);

void addSuccessor(BasicBlock* block, int successorIndex);

void addBasicBlock(CFG* cfg, BasicBlock* block);

CFG* initEmptyCFG();

void freeCFG(CFG* cfg);

#endif
