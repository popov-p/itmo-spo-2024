#pragma once

#include <antlr3.h>
#include "TreeBuilder.h"

#define AST_TOKEN_IS(node, str) (!strcmp((node->token), (str)))

#define AST_TOKEN_CONVERTS_TO_INT(node) ({            \
    char* endptr;                                 \
    strtol((node)->token, &endptr, 10);           \
    (*endptr == '\0');                            \
})
typedef struct AST {
  uint32_t id;
  char* token;
  struct AST* parent;
  struct AST** children;
  size_t childCount;
} AST;

AST* AST_CreateNode(uint32_t id, char* token);
void AST_AddChild(AST* parent, AST* child);
void AST_Free(AST* head);

void AST_InsertBetween(AST* parent, AST* thatChild, AST* thisNode);

AST* AST_FindNodeById(AST* node, uint32_t id);
AST* AST_BuildFromParseResult(ParseResult* parseResult);
void AST_SetChildFromAntlrNode(AST* parent,
                           pANTLR3_BASE_TREE_ADAPTOR adaptor,
                           pANTLR3_BASE_TREE node);
AST* AST_GetChild(AST* parent, size_t i);


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
