#include "OTOutput.h"
#include <stdio.h>

void OT_PrintTree(OT* node, int level) {
  if (!node)
    return;

  for (int i = 0; i < level; i++)
    printf("  ");

  printf("Node ID: %u, Type: ", node->id);

  switch (node->dataType) {
    case OT_OPERATION:
      printf("Operation, ReturnType: %s, OperationType: %s\n",
             node->data.operation.returnType ? node->data.operation.returnType : "NULL",
             node->data.operation.operationType ? node->data.operation.operationType : "NULL");
      break;

    case OT_VARIABLE:
      printf("Variable, Name: %s, VarType: %s\n",
             node->data.variable.name ? node->data.variable.name : "NULL",
             node->data.variable.varType ? node->data.variable.varType : "NULL");
      break;

    case OT_FUNCTION:
      printf("Function, Name: %s, ReturnType: %s\n",
             node->data.function.name ? node->data.function.name : "NULL",
             node->data.function.returnType ? node->data.function.returnType : "NULL");
      break;

    case OT_CONSTANT:
      printf("Constant, Value: %s, ConstType: %s\n",
             node->data.constant.value ? node->data.constant.value : "NULL",
             node->data.constant.constType ? node->data.constant.constType : "NULL");
      break;

    default:
      printf("Unknown Type\n");
      break;
  }

  for (int i = 0; i < node->childCount; i++) {
    OT_PrintTree(node->children[i], level + 1);
  }
}


void OT_WriteNode(OT* node, int basicBlockIndex, FILE *file) {
  if (!node || !file) return;

  switch (node->dataType) {
    case OT_OPERATION:
      fprintf(file, "    cluster_%d_node%u [label=\"Operation: %s (%s)\"];\n",
              basicBlockIndex, node->id,
              node->data.operation.operationType,
              node->data.operation.returnType);
      break;
    case OT_VARIABLE:
      fprintf(file, "    cluster_%d_node%u [label=\"Variable: %s (%s)\"];\n",
              basicBlockIndex, node->id,
              node->data.variable.name,
              node->data.variable.varType);
      break;
    case OT_FUNCTION:
      fprintf(file, "    cluster_%d_node%u [label=\"Function: %s (%s)\"];\n",
              basicBlockIndex, node->id,
              node->data.function.name,
              node->data.function.returnType);
      break;
    case OT_CONSTANT:
      fprintf(file, "    cluster_%d_node%u [label=\"Constant: %s (%s)\"];\n",
              basicBlockIndex, node->id,
              node->data.constant.value,
              node->data.constant.constType);
      break;
    default:
      fprintf(file, "    cluster_%d_node%u [label=\"Unknown\"];\n",
              basicBlockIndex, node->id);
  }
}

void OT_WriteEdge(OT* parent, OT* child, int basicBlockIndex, FILE *file) {
  if (!parent || !child || !file) return;

  fprintf(file, "    cluster_%d_node%u -> cluster_%d_node%u;\n",
          basicBlockIndex, parent->id, basicBlockIndex, child->id);
}

void OT_WriteNodes(OT* node, int basicBlockIndex, FILE *file) {
  if (!node) return;

  int childCount = node->childCount;

  OT_WriteNode(node, basicBlockIndex, file);
  for (int i = 0; i < childCount; i++) {
    OT* child = OT_GetChild(node, i);
    OT_WriteNodes(child, basicBlockIndex, file);
  }
}

void OT_WriteEdges(OT* parent, int basicBlockIndex, FILE *file) {
  if(!parent)
    return;
  int childCount = parent->childCount;

  for (int i = 0; i < childCount; i++) {
    OT* child = OT_GetChild(parent, i);

    OT_WriteEdge(parent, child, basicBlockIndex, file);
    OT_WriteEdges(child, basicBlockIndex, file);
  }
}
