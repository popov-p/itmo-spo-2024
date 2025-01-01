#ifndef  CFGNODEPROCESSING_H
#define CFGNODEPROCESSING_H

#include "AST.h"
#include "CFG.h"

void cfgWalker(CFG* cfg,
               AST* node);

int cfgWalkerLinkWithParent(CFG* cfg,
                            AST* current);

int cfgWalkerLinkWithSpecific(CFG* cfg,
                              AST* current,
                              int specificBlockIndex);

void enteringIf(CFG* cfg,
                AST* node);

void enteringElse(CFG* cfg,
                  AST* node);

void enteringLoop(CFG* cfg,
                  AST* node);

void cfgWalkerProcessCallNode(CFG* cfg,
                              AST* node);

void enteringRepeat(CFG* cfg,
                    AST* node);

void cfgWalkerProcessBlockNode(CFG* cfg,
                                AST* node);

void cfgWalkerProcessVarDecNode(CFG* cfg,
                                AST* node);

void cfgWalkerProcessVarDefNode(CFG* cfg,
                                AST* node);

void cfgWalkerProcessBreakNode(CFG* cfg,
                                AST* node);

void cfgWalkerProcessAssignment(CFG* cfg,
                               AST* node);
#endif
