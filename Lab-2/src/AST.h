#ifndef AST_H
#define AST_H

#include <antlr3.h>
#include "TreeBuilder.h"

typedef struct AST {
    uint32_t id;
    char* token;
    struct AST* parent;
    struct AST** children;
    size_t child_count;
} AST;

AST* createNode(uint32_t id, char* token);
void addChild(AST* parent, AST* child);
void freeTree(AST* node);

AST* findNodeById(AST* node, uint32_t id);

AST* buildFromParseResult(pParseResult parseResult);
void setChildFromAntlrNode(AST* parent, pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE node);

AST* getChild(AST* parent, size_t i);
AST* getParent(AST* node);
void printAST(AST* head, FILE* file);
void outputAST(AST* head, FILE* file);
void writeNode(AST* node, int basicBlockIndex, FILE *file);

void writeEdge(AST* parent, AST* child, int basicBlockIndex, FILE *file);

void outputOpNode(AST* node,
                  int basicBlockIndex,
                  FILE *file);

void outputOpEdge(AST* parent,
                  int basicBlockIndex,
                  FILE *file);

pANTLR3_BASE_TREE analyzeOp (pParseResult parseResult,
                            pANTLR3_BASE_TREE node);

void analyzeCall(pANTLR3_BASE_TREE_ADAPTOR adaptor,
                 pANTLR3_BASE_TREE node);
#endif
