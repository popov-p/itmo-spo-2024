#ifndef  CFGNODEPROCESSING_H
#define CFGNODEPROCESSING_H

#include "AST.h"
#include "BasicBlock.h"

void cfgWalker(CFG* cfg,
               AST* node,
               int* lastBlockIndex);

int cfgWalkerLinkWithParent(CFG* cfg,
                            AST* current,
                            int* lastBlockIndex);

void cfgWalkerProcessIfNode(CFG* cfg,
                            AST* node,
                            int* lastBlockIndex,
                            int* childCount,
                            int* breakDetected);

void cfgWalkerProcessCallNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex,
                              int* childCount);


void cfgWalkerProcessLoopNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex,
                              int* childCount,
                              int* breakDetected);

void cfgWalkerProcessRepeatNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex,
                                int* childCount);

void cfgWalkerProcessBlockNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex,
                                int* childCount);

void cfgWalkerProcessVarDecNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex,
                                int* childCount);

void cfgWalkerProcessVarDefNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex,
                                int* childCount);

void cfgWalkerProcessBreakNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex,
                                int* childCount);

void cfgWalkerProcessAssignment(CFG* cfg,
                               AST* node,
                               int* lastBlockIndex,
                               int* childCount);


#endif
