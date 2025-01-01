#pragma once

#include "CFG.h"

CFG* generateCFG(AST* head);
void outputCFG(CFG* cfg, FILE* file);
void outputSubgraph(CFG* cfg,
                    int basicBlockIndex, FILE* file);
void writeBlock(int num, FILE *file, BB_t type);
void writeCFGEdges(CFG* cfg, FILE *file);
