#include "OTOutput.h"

void OT_PrintTree(OT* node, int level) {
  if (!node)
    return;
  for (int i = 0; i < level; i++)
    printf("  ");
  printf("PT :: ID IS: %d, TOKEN - %s\n", node->id, node->token);

  for (size_t i = 0; i < node->childCount; i++)
    OT_PrintTree(node->children[i], level + 1);
}

void OT_WriteNode(OT* node, int basicBlockIndex, FILE *file) {
  fprintf(file, "    cluster_%d_node%u [label=\"%s\"];\n", basicBlockIndex,
          node->id, node->token);
}

void OT_WriteEdge(OT* parent, OT* child, int basicBlockIndex, FILE *file) {
  fprintf(file, "    cluster_%d_node%u -> cluster_%d_node%u;\n",
          basicBlockIndex, parent->id, basicBlockIndex, child->id);
}

void OT_OutputNode(OT* node, int basicBlockIndex, FILE *file) {
  if (!node) return;

  int childCount = node->childCount;

  OT_WriteNode(node, basicBlockIndex, file);
  for (int i = 0; i < childCount; i++) {
    OT* child = OT_GetChild(node, i);
    OT_OutputNode(child, basicBlockIndex, file);
  }
}

void OT_OutputEdge(OT* parent, int basicBlockIndex, FILE *file) {
  if(!parent)
    return;
  int childCount = parent->childCount;

  for (int i = 0; i < childCount; i++) {
    OT* child = OT_GetChild(parent, i);

    OT_WriteEdge(parent, child, basicBlockIndex, file);
    OT_OutputEdge(child, basicBlockIndex, file);
  }
}
