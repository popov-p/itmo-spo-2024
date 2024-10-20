#ifndef OPTREE_H
#define OPTREE_H

#include <antlr3.h>
#include "TreeBuilder.h"
#include "BasicBlock.h"

void writeNode(pANTLR3_BASE_TREE tree, uint32_t* id, int basicBlockIndex, FILE *file);
void writeEdge(uint32_t* parentId, uint32_t* childId, int basicBlockIndex, FILE *file);

void outputOpNode(pANTLR3_BASE_TREE_ADAPTOR adaptor,
                  pANTLR3_BASE_TREE node,
                  int basicBlockIndex,
                  FILE *file);
void outputSubgraph(pParseResult parseResult, CFG* cfg,
                  int basicBlockIndex, FILE* file);

void outputOpEdge(pANTLR3_BASE_TREE_ADAPTOR adaptor,
                  pANTLR3_BASE_TREE node, int basicBlockIndex,
                  FILE *file);
// void outputOpEdges(pParseResult parseResult, CFG* cfg,
//                   int basicBlockIndex, FILE* file);
#endif
