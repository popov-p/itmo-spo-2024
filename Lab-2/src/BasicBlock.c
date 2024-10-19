#include "BasicBlock.h"
#include <stdlib.h>
#include <stdio.h>

BasicBlock* createBasicBlock(int id) {
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

CFG* createCFG() {
    CFG* cfg = (CFG*)malloc(sizeof(CFG));
    cfg->blocks = NULL;
    cfg->block_count = 0;

    BasicBlock* startBlock = createBasicBlock(-1);
    addBasicBlock(cfg, startBlock);

    BasicBlock* endBlock = createBasicBlock(-2);
    addBasicBlock(cfg, endBlock);

    return cfg;
}

void printCFG(CFG* cfg) {
    for (int i = 0; i < cfg->block_count; i++) {
        BasicBlock* block = cfg->blocks[i];
        printf("Block %d:\n", block->id);
        printf("  Successors: ");
        for (int j = 0; j < block->successor_count; j++) {
            printf("%d ", cfg->blocks[block->successors[j]]->id);
        }
        printf("\n");
    }
}

void freeCFG(CFG* cfg) {
    for (int i = 0; i < cfg->block_count; i++) {
        free(cfg->blocks[i]->successors);
        free(cfg->blocks[i]);
    }
    free(cfg->blocks);
    free(cfg);
}
