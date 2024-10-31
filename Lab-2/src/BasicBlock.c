#include "BasicBlock.h"
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
    block->successors = (int*)realloc(block->successors, block->successorCount * sizeof(int));
    block->successors[block->successorCount - 1] = successorIndex;
}

void addBasicBlock(CFG* cfg, BasicBlock* block) {
    cfg->blockCount++;
    cfg->blocks = (BasicBlock**)realloc(cfg->blocks, cfg->blockCount * sizeof(BasicBlock*));
    cfg->blocks[cfg->blockCount - 1] = block;
}

CFG* initEmptyCFG(int processedNodesSize, int loopLevelStackSize) {
    CFG* cfg = (CFG*)malloc(sizeof(CFG));
    cfg->blocks = NULL;
    cfg->blockCount = 0;
    cfg->processedNodes = createProcessedNodes(processedNodesSize);
    cfg->loopLevelStack = createLoopLevelStack(loopLevelStackSize);
    return cfg;
}

void freeCFG(CFG* cfg) {
    for (int i = 0; i < cfg->blockCount; i++) {
        free(cfg->blocks[i]->successors);
        free(cfg->blocks[i]);
    }
    free(cfg->blocks);
    free(cfg);
}
