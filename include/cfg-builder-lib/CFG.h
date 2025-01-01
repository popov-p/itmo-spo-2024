#pragma once
#include "AST.h"
#include "LevelStack.h"
#include "OT.h"

typedef enum BB_t {
  standard,
  merge,
  loop_exit,
  repeat_exit
}BB_t;

typedef struct BB {
  AST* node;
  OT* opTree;
  BB_t bt;
  int* successors; //sucessors` indices in BasicBlock** array
  int successorCount;
} BB;

typedef struct CFG {
  BB** blocks;
  int blockCount;
  int lastProcessedIndex;
  LoopLevelStack* loopLevelStack;
  IfLevelStack* ifLevelStack;

} CFG;

CFG* generateCFG(AST* head);
BB* createBasicBlock(AST* node, enum BB_t bt);
void addSuccessor(BB* block, int successorIndex);
void addBasicBlock(CFG* cfg, BB* block);


CFG* initEmptyCFG(int processedNodesSize, int loopLevelStackSize, int ifLevelStackSize);
void freeCFG(CFG* cfg);
