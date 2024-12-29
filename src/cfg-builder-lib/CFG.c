    #include "CFG.h"
#include <stdlib.h>
#include <stdio.h>

BasicBlock* createBasicBlock(AST* node, enum BasicBlockType bt) {
    BasicBlock* block = (BasicBlock*)malloc(sizeof(BasicBlock));
    block->node = node;
    block->bt = bt;
    block->successors = NULL;
    block->successorCount = 0;
    return block;
}

void addSuccessor(BasicBlock* block, int successorIndex) {
    block->successorCount++;
    int* newSuccessors = (int*)realloc(block->successors, block->successorCount * sizeof(int));
    if (!newSuccessors) {
        fprintf(stderr, "ERROR :: REALLOC FAILED\n");
        block->successorCount--;
        return;
    }
    block->successors = newSuccessors;
    block->successors[block->successorCount - 1] = successorIndex;
}

void addBasicBlock(CFG* cfg, BasicBlock* block) {
    cfg->blockCount++;
    BasicBlock** newBlocks = (BasicBlock**)realloc(cfg->blocks, cfg->blockCount * sizeof(BasicBlock*));
    if (!newBlocks) {
        fprintf(stderr, "ERROR :: REALLOC FAILED\n");
        cfg->blockCount--;
        return;
    }
    cfg->blocks = newBlocks;
    cfg->blocks[cfg->blockCount - 1] = block;
}

CFG* initEmptyCFG(int processedNodesSize, int loopLevelStackSize, int ifLevelStackSize) {
    CFG* cfg = (CFG*)malloc(sizeof(CFG));
    cfg->blocks = NULL;
    cfg->blockCount = 0;
    cfg->processedNodes = createProcessedNodes(processedNodesSize);
    cfg->loopLevelStack = createLoopLevelStack(loopLevelStackSize);
    cfg->ifLevelStack = createIfLevelStack(ifLevelStackSize);
    return cfg;
}

void freeCFG(CFG* cfg) {
    for (int i = 0; i < cfg->blockCount; i++) {
        free(cfg->blocks[i]->successors);
        free(cfg->blocks[i]);
    }

    freeIfLevelStack(cfg->ifLevelStack);
    freeLoopLevelStack(cfg->loopLevelStack);
    freeProcessedNodes(cfg->processedNodes);

    free(cfg->blocks);
    free(cfg);
}
