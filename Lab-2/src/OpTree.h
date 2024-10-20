#ifndef OPTREE_H
#define OPTREE_H

#include <antlr3.h>
#include "TreeBuilder.h"
#include "BasicBlock.h"

typedef struct AST {
    uint32_t id;
    char* token;
    struct AST* parent;
    struct AST** children;
    size_t numChildren;
} AST;

AST* createNode(uint32_t id, const char* token);
void addChild(AST* parent, AST* child);
void freeTree(AST* node);

AST* findNodeById(AST* node, uint32_t id);










void writeNode(pANTLR3_BASE_TREE tree, uint32_t* id,
               int basicBlockIndex, FILE *file);

void writeEdge(uint32_t* parentId, uint32_t* childId,
               int basicBlockIndex, FILE *file);

void outputOpNode(pANTLR3_BASE_TREE_ADAPTOR adaptor,
                  pANTLR3_BASE_TREE node,
                  int basicBlockIndex,
                  FILE *file);

void outputOpEdge(pANTLR3_BASE_TREE_ADAPTOR adaptor,
                  pANTLR3_BASE_TREE node, int basicBlockIndex,
                  FILE *file);

void outputSubgraph(pParseResult parseResult, CFG* cfg,
                    int basicBlockIndex, FILE* file);

pANTLR3_BASE_TREE analyzeOp (pParseResult parseResult,
                            pANTLR3_BASE_TREE node);

void analyzeCall(pANTLR3_BASE_TREE_ADAPTOR adaptor,
                 pANTLR3_BASE_TREE node);
#endif
