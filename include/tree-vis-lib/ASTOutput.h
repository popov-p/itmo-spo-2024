#pragma once
#include "AST.h"

void AST_WriteInFile(AST* head, FILE* file);
void AST_WriteNodes(AST* node, FILE* file);
void AST_WriteEdges(AST* node, FILE* file);
void AST_WriteEdge(AST* parent, AST* child, FILE* file);
void AST_WriteNode(AST* node, FILE *file);

void AST_printTree(AST* node, int level);
