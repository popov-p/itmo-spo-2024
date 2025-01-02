#pragma once

#include <antlr3.h>
#include "TreeBuilder.h"

#define TOKEN_IS(node, str) (!strcmp((node->token), (str)))

typedef struct AST {
  uint32_t id;
  char* token;
  struct AST* parent;
  struct AST** children;
  size_t childCount;
} AST;

AST* createNode(uint32_t id, char* token);
void addChild(AST* parent, AST* child);
void freeAST(AST* head);

void insertBetween(AST* parent, AST* thatChild, AST* thisNode);
AST* duplicateTree(AST* head);
AST* duplicateTreeRecursive(AST* head);

AST* findNodeById(AST* node, uint32_t id);
AST* buildFromParseResult(ParseResult* parseResult);
void setChildFromAntlrNode(AST* parent,
                           pANTLR3_BASE_TREE_ADAPTOR adaptor,
                           pANTLR3_BASE_TREE node);
AST* getChild(AST* parent, size_t i);


// void outputAST(AST* head, FILE* file);
// void outputASTNodes(AST* head, FILE* file);
// void outputASTEdges(AST* node, FILE* file);
// void writeNode(AST* node, int basicBlockIndex, FILE *file);

// void writeEdge(AST* parent, AST* child, int basicBlockIndex, FILE *file);

// void outputOpNode(AST* node,
//                   int basicBlockIndex,
//                   FILE *file);

// void outputOpEdge(AST* parent,
//                   int basicBlockIndex,
//                   FILE *file);

// AST* analyzeOp (AST* node);
