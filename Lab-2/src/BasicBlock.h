#ifndef BASICBLOCK_H
#define BASICBLOCK_H

typedef struct CFG {
    struct BasicBlock** blocks;
    int block_count;
} CFG;

typedef struct BasicBlock {
    int id;
    int* successors;
    int successor_count;
} BasicBlock;

BasicBlock* createBasicBlock(int id);

void addSuccessor(BasicBlock* block, int successorIndex);

void addBasicBlock(CFG* cfg, BasicBlock* block);

CFG* createCFG();

void printCFG(CFG* cfg);

void freeCFG(CFG* cfg);

#endif
