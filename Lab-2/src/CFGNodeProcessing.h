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
                            int* lastBlockIndex);

void cfgWalkerProcessCallNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex);


void cfgWalkerProcessLoopNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex,
                              int* breakDetected);

void cfgWalkerProcessRepeatNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex);

void cfgWalkerProcessBlockNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex);

void cfgWalkerProcessVarDecNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex);

void cfgWalkerProcessVarDefNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex);

void cfgWalkerProcessBreakNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex,
                                int* breakDetected);

void cfgWalkerProcessAssignment(CFG* cfg,
                               AST* node,
                               int* lastBlockIndex);


#endif
