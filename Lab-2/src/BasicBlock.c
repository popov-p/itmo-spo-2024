#include "BasicBlock.h"
#include <stdlib.h>
#include <stdio.h>

BasicBlock* createBasicBlock(uint32_t id) {
    BasicBlock* block = (BasicBlock*)malloc(sizeof(BasicBlock));
    block->id = id;
    block->successors = NULL;
    block->successor_count = 0;
    return block;
}

void addSuccessor(BasicBlock* block, int successorIndex) {
    block->successor_count++;
    block->successors = (int*)realloc(block->successors, block->successor_count * sizeof(int));
    block->successors[block->successor_count - 1] = successorIndex;
}

void addBasicBlock(CFG* cfg, BasicBlock* block) {
    cfg->block_count++;
    cfg->blocks = (BasicBlock**)realloc(cfg->blocks, cfg->block_count * sizeof(BasicBlock*));
    cfg->blocks[cfg->block_count - 1] = block;
}

CFG* initEmptyCFG() {
    CFG* cfg = (CFG*)malloc(sizeof(CFG));
    cfg->blocks = NULL;
    cfg->block_count = 0;

    return cfg;
}

void freeCFG(CFG* cfg) {
    for (int i = 0; i < cfg->block_count; i++) {
        free(cfg->blocks[i]->successors);
        free(cfg->blocks[i]);
    }
    free(cfg->blocks);
    free(cfg);
}
