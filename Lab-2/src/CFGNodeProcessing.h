#ifndef  CFGNODEPROCESSING_H
#define CFGNODEPROCESSING_H

#include "AST.h"
#include "BasicBlock.h"
#include "ProcessedNodes.h"

void cfgWalker(CFG* cfg, AST* node, int* lastBlockIndex, ProcessedNodes* processedNodes);
void cfgWalkerProcessIfNode(CFG* cfg,
                            AST* node,
                            int* lastBlockIndex,
                            ProcessedNodes* processedNodes,
                            int* childCount);

void cfgWalkerProcessCallNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex,
                              ProcessedNodes* processedNodes,
                              int* childCount);


void cfgWalkerProcessLoopNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex,
                              ProcessedNodes* processedNodes,
                              int* childCount);

void cfgWalkerProcessRepeatNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex,
                              ProcessedNodes* processedNodes,
                              int* childCount);



#endif
