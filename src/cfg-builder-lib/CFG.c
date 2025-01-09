#include "CFG.h"
#include <stdlib.h>
#include <stdio.h>
#include "safe_mem.h"
#include "CFGWalker.h"
// #include "OTOutput.h"

BB* CFG_CreateBB(AST* node, BB_t bt) {
  BB* block = (BB*)safe_malloc(sizeof(BB));
  block->node = node;
  block->bt = bt;
  block->opTree = NULL;
  block->successors = NULL;
  block->successorCount = 0;
  return block;
}

void CFG_AddSuccessor(BB* block, int successorIndex) {
  block->successorCount++;
  int* newSuccessors = (int*)safe_realloc(block->successors,
                                          block->successorCount * sizeof(int));
  block->successors = newSuccessors;
  block->successors[block->successorCount - 1] = successorIndex;
}

void CFG_GenerateOTs(CFG* cfg, ST* st) {
  ST_Print(st);
  if (!cfg || !cfg->blocks || cfg->blockCount <= 0) {
    printf("CFG or basic blocks are invalid.\n");
    return;
  }

  for (int i = 0; i < cfg->blockCount; i++) {
    BB* block = cfg->blocks[i];
    if (block && block->node) {
      block->opTree = OT_BuildFromAST(st, block->node);
      continue;
    }
  }

  for (int i = 0; i < cfg->blockCount; i++) {
    BB* block = cfg->blocks[i];
    if (block && block->node) {
      // OT_PrintTree(block->opTree, 0);
      // printf("=================>\n");
    }
  }
}

CFG* CFG_Generate(AST* head) {
  CFG* cfg = CFG_Init(20, 20);
  CFG_Walker(cfg, head);
  ST* st = ST_BuildFromFAST(head);
  CFG_GenerateOTs(cfg, st);
  return cfg;
}

void CFG_AddBB(CFG* cfg, BB* block) {
  cfg->blockCount++;
  BB** newBlocks = (BB**)safe_realloc(cfg->blocks,
                                      cfg->blockCount * sizeof(BB*));
  cfg->blocks = newBlocks;
  cfg->blocks[cfg->blockCount - 1] = block;
}

CFG* CFG_Init(int loopLevelStackSize,
              int ifLevelStackSize) {
  CFG* cfg = (CFG*)safe_malloc(sizeof(CFG));
  cfg->symbolTable = NULL;
  cfg->blocks = NULL;
  cfg->blockCount = 0;
  cfg->lastProcessedIndex = -1;
  cfg->loopStack = LS_Create(loopLevelStackSize);
  cfg->ifStack = IS_Create(ifLevelStackSize);
  return cfg;
}

void CFG_Free(CFG* cfg) {
  for (int i = 0; i < cfg->blockCount; i++) {
    free(cfg->blocks[i]->successors);
    free(cfg->blocks[i]->opTree);
    free(cfg->blocks[i]);
  }

  IS_Free(cfg->ifStack);
  LS_Free(cfg->loopStack);
  free(cfg->blocks);
  free(cfg);
}
