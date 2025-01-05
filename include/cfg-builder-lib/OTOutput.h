#pragma once
#include "OT.h"

void OT_PrintTree(OT* node, int level);
void OT_WriteNode(OT* node, int basicBlockIndex, FILE *file);
void OT_WriteEdge(OT* parent, OT* child, int basicBlockIndex, FILE *file);
void OT_WriteNodes(OT* node, int basicBlockIndex, FILE *file);
void OT_WriteEdges(OT* parent, int basicBlockIndex, FILE* file);
