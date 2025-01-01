#include "CFG.h"
#include <stdlib.h>
#include <stdio.h>
#include "safe_mem.h"

BasicBlock* createBasicBlock(AST* node, enum BasicBlockType bt) {
  BasicBlock* block = (BasicBlock*)safe_malloc(sizeof(BasicBlock));
  block->node = node;
  block->bt = bt;
  block->successors = NULL;
  block->successorCount = 0;
  return block;
}

void addSuccessor(BasicBlock* block, int successorIndex) {
  block->successorCount++;
  int* newSuccessors = (int*)safe_realloc(block->successors, block->successorCount * sizeof(int));
  block->successors = newSuccessors;
  block->successors[block->successorCount - 1] = successorIndex;
}

void addBasicBlock(CFG* cfg, BasicBlock* block) {
  cfg->blockCount++;
  BasicBlock** newBlocks = (BasicBlock**)safe_realloc(cfg->blocks, cfg->blockCount * sizeof(BasicBlock*));
  cfg->blocks = newBlocks;
  cfg->blocks[cfg->blockCount - 1] = block;
}

CFG* initEmptyCFG(int processedNodesSize, int loopLevelStackSize, int ifLevelStackSize) {
  CFG* cfg = (CFG*)safe_malloc(sizeof(CFG));
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
