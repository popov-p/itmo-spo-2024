#include "ASTOutput.h"

void AST_WriteInFile(AST* head, FILE* file) {
  fprintf(file, "digraph AST {\n");
  fprintf(file, "    node [shape=box];\n");

  AST_WriteNodes(head, file);
  AST_WriteEdges(head, file);
  fprintf(file, "}\n");
}

void AST_WriteEdges(AST* node, FILE* file) {
  for (size_t i = 0; i < node->childCount; i++) {
    AST* child = AST_GetChild(node, i);
    AST_WriteEdge(node, child, file);
    AST_WriteEdges(child, file);
  }
}

void AST_WriteNodes(AST* node, FILE* file) {
  if (!node) return;
  AST_WriteNode(node, file);
  for (size_t i = 0; i < node->childCount; i++) {
    AST* child = AST_GetChild(node, i);
    AST_WriteNodes(child, file);
  }
}

void AST_WriteNode(AST* node, FILE *file) {
  fprintf(file, "    node%u [label=\"%s\"];\n",
          node->id, node->token);
}

void AST_WriteEdge(AST* parent, AST* child, FILE *file) {
  fprintf(file, "    node%u -> node%u;\n", parent->id, child->id);
}

void AST_printTree(AST* node, int level) {
  if (!node)
    return;
  for (int i = 0; i < level; i++)
    printf("  ");
  printf("PT :: ID: %u, TOKEN: %s\n", node->id, node->token);

  for (size_t i = 0; i < node->childCount; i++)
    AST_printTree(node->children[i], level + 1);
}
