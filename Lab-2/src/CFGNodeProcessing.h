#ifndef  CFGNODEPROCESSING_H
#define CFGNODEPROCESSING_H

#include "AST.h"
#include "CFG.h"

void cfgWalker(CFG* cfg,
               AST* node,
               int* lastBlockIndex);

int cfgWalkerLinkWithParent(CFG* cfg,
                            AST* current,
                            int* lastBlockIndex);

int cfgWalkerLinkWithSpecific(CFG* cfg,
                              AST* current,
                              int specificBlockIndex);

void enteringIf(CFG* cfg,
                AST* node,
                int* lastBlockIndex);

void enteringElse(CFG* cfg,
                  AST* node,
                  int* lastBlockIndex);

void cfgWalkerProcessCallNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex);

void enteringLoop(CFG* cfg,
                 AST* node,
                 int* lastBlockIndex);

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
                                int* lastBlockIndex);

void cfgWalkerProcessAssignment(CFG* cfg,
                               AST* node,
                               int* lastBlockIndex);
#endif
