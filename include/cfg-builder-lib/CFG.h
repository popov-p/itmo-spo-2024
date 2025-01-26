#pragma once
#include "AST.h"
#include "LevelStack.h"
#include "OT.h"
#include "ST.h"

typedef enum BB_t {
  standard,
  merge,
  loop_exit,
  repeat_exit
} BB_t;

typedef struct BB {
  AST* node;
  OT* opTree;
  BB_t bt;
  int* successors; //sucessors` indices in BasicBlock** array
  int successorCount;
} BB;

typedef struct CFG {
  ST* symbolTable;
  BB** blocks;
  int blockCount;
  int lastProcessedIndex;
  LS* loopStack;
  IS* ifStack;

} CFG;

CFG* CFG_Generate(AST* head);
void CFG_GenerateOTs(CFG* cfg, ST* st);
BB* CFG_CreateBB(AST* node, enum BB_t bt);
void CFG_AddSuccessor(BB* block, int successorIndex);
void CFG_AddBB(CFG* cfg, BB* block);
CFG* CFG_Init(int loopLevelStackSize, int ifLevelStackSize);
void CFG_Free(CFG* cfg);
