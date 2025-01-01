#include "CFG.h"
#include <stdlib.h>
#include <stdio.h>
#include "safe_mem.h"
#include "CFGWalker.h"

BB* createBasicBlock(AST* node, BB_t bt) {
  BB* block = (BB*)safe_malloc(sizeof(BB));
  block->node = node;
  block->bt = bt;
  block->opTree = NULL;
  block->successors = NULL;
  block->successorCount = 0;
  return block;
}

void addSuccessor(BB* block, int successorIndex) {
  block->successorCount++;
  int* newSuccessors = (int*)safe_realloc(block->successors, block->successorCount * sizeof(int));
  block->successors = newSuccessors;
  block->successors[block->successorCount - 1] = successorIndex;
}

CFG* generateCFG(AST* head) {
  CFG* cfg = initEmptyCFG(100, 20, 20);
  cfgWalker(cfg, head);
  return cfg;
}

void addBasicBlock(CFG* cfg, BB* block) {
  cfg->blockCount++;
  BB** newBlocks = (BB**)safe_realloc(cfg->blocks, cfg->blockCount * sizeof(BB*));
  cfg->blocks = newBlocks;
  cfg->blocks[cfg->blockCount - 1] = block;
}

CFG* initEmptyCFG(int processedNodesSize,
                  int loopLevelStackSize,
                  int ifLevelStackSize) {
  CFG* cfg = (CFG*)safe_malloc(sizeof(CFG));
  cfg->blocks = NULL;
  cfg->blockCount = 0;
  cfg->lastProcessedIndex = -1;
  cfg->loopLevelStack = createLoopLevelStack(loopLevelStackSize);
  cfg->ifLevelStack = createIfLevelStack(ifLevelStackSize);
  return cfg;
}

void freeCFG(CFG* cfg) {
  for (int i = 0; i < cfg->blockCount; i++) {
    free(cfg->blocks[i]->successors);
    free(cfg->blocks[i]->opTree);
    free(cfg->blocks[i]);
  }

  freeIfLevelStack(cfg->ifLevelStack);
  freeLoopLevelStack(cfg->loopLevelStack);
  free(cfg->blocks);
  free(cfg);
}
