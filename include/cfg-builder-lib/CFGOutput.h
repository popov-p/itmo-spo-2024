#pragma once

#include "CFG.h"

void CFG_WriteInFile(CFG* cfg, FILE* file);
void CFG_WriteOT(CFG* cfg,
                 int basicBlockIndex, FILE* file);
void CFG_WriteBlock(int num, FILE *file, BB_t type);
void CFG_WriteEdges(CFG* cfg, FILE *file);
