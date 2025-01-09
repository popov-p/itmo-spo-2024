#include <stdlib.h>
#include <string.h>
#include "OT.h"
#include "safe_mem.h"
#include "ST.h"

#define __READ  "OP_READ"
#define __WRITE  "OP_WRITE"
#define __PLACE "OP_PLACE"
#define __CONST "OP_CONST"
#define __CALL "OP_CALL"
#define __HEAD "OP_HEAD"

OT* OT_GetChild(const OT* parent, int index) {
  if (!parent || index < 0 || index >= parent->childCount)
    return NULL;
  return parent->children[index];
}

OT* OT_CreateNode(AST* astNode,
                  OT_t dataType,
                  const char* primaryData,
                  const char* secondaryData) {
  if (!astNode)
    return NULL;

  OT* otNode = (OT*)safe_malloc(sizeof(OT));
  otNode->dataType = dataType;
  otNode->parent = NULL;
  otNode->children = NULL;
  otNode->childCount = 0;
  otNode->id = astNode->id;

  switch (dataType) {
    case OT_OPERATION:
      otNode->data.operation.returnType = primaryData ? strdup(primaryData) : NULL;
      otNode->data.operation.operationType = secondaryData ? strdup(secondaryData) : NULL;
      break;
    case OT_VARIABLE:
      otNode->data.variable.name = primaryData ? strdup(primaryData) : NULL;
      otNode->data.variable.varType = secondaryData ? strdup(secondaryData) : NULL;
      break;
    case OT_FUNCTION:
      otNode->data.function.name = primaryData ? strdup(primaryData) : NULL;
      otNode->data.function.returnType = secondaryData ? strdup(secondaryData) : NULL;
      break;
    case OT_CONSTANT:
      otNode->data.constant.value = primaryData ? strdup(primaryData) : NULL;
      otNode->data.constant.constType = secondaryData ? strdup(secondaryData) : NULL;
    case OT_AUX:
      otNode->data.auxiliary.firstOption = primaryData ? strdup(primaryData) : NULL;
      otNode->data.auxiliary.secondOption = secondaryData ? strdup(secondaryData) : NULL;
      break;
    default:
      printf("%s", "Error while building OT from AST. Exiting ...\n");
      exit(EXIT_FAILURE);
  }

  return otNode;
}

OT* OT_CreateAuxiliaryNode(OT_t dataType,
                           const char* primaryData,
                           const char* secondaryData) {

  OT* otNode = (OT*)safe_malloc(sizeof(OT));
  otNode->dataType = dataType;
  otNode->parent = NULL;
  otNode->children = NULL;
  otNode->childCount = 0;
  otNode->id = arc4random();

  switch (dataType) {
    case OT_OPERATION:
      otNode->data.operation.returnType = primaryData ? strdup(primaryData) : NULL;
      otNode->data.operation.operationType = secondaryData ? strdup(secondaryData) : NULL;
      break;
    default:
      printf("%s", "Error while creating auxiliary OT node. Exiting ...\n");
      exit(EXIT_FAILURE);
  }

  return otNode;
}

void OT_AddChild(OT* parent, OT* child) {
  if(!parent || !child)
    return;
  parent->children = safe_realloc(parent->children, (parent->childCount + 1) * sizeof(OT*));
  parent->children[parent->childCount] = child;
  parent->childCount++;

  child->parent = parent;
}

void OT_RemoveChild(OT* parent, OT* child) {
  if (!parent || !child) return;

  int childIndex = -1;
  for (int i = 0; i < parent->childCount; i++) {
    if (parent->children[i] == child) {
      childIndex = i;
      break;
    }
  }

  if (childIndex == -1) return;
  child->parent = NULL;
  for (int i = childIndex; i < parent->childCount - 1; i++)
    parent->children[i] = parent->children[i + 1];
  parent->childCount--;

  parent->children = safe_realloc(parent->children, parent->childCount * sizeof(OT*));
}

void OT_InsertBetween(OT* parent,
                      OT* thatChild,
                      OT* thisNode) {
  if (!parent || !thatChild || !thisNode) return;

  OT_RemoveChild(parent, thatChild);
  OT_AddChild(parent, thisNode);
  OT_AddChild(thisNode, thatChild);
}

void OT_Free(OT* node) {
  if (!node) return;

  switch (node->dataType) {
    case OT_OPERATION:
      free(node->data.operation.returnType);
      free(node->data.operation.operationType);
      break;
    case OT_VARIABLE:
      free(node->data.variable.name);
      free(node->data.variable.varType);
      break;
    case OT_FUNCTION:
      free(node->data.function.name);
      free(node->data.function.returnType);
      break;
    case OT_CONSTANT:
      free(node->data.constant.value);
      free(node->data.constant.constType);
      break;
    default:
      break;
  }

  if (node->children) {
    for (int i = 0; i < node->childCount; i++) {
      OT_Free(node->children[i]);
    }
    free(node->children);
  }
  free(node);
}

OT* OT_BuildFromAST(ST* st, AST* node) {
  if (!node) return NULL;
  OT* ot = OT_CreateAuxiliaryNode(OT_OPERATION, NULL, __HEAD);
  OT_Walker(ot, st, node);
  OT_TypeResolver(ot);
  return ot;
}

void OT_Walker(OT* ot, ST* st, AST* node) {
  if (!node) return;
  OT* currentNode = NULL;

  if (AST_TOKEN_IS(node, "AST_PLUS") ||
      AST_TOKEN_IS(node, "AST_MINUS") ||
      AST_TOKEN_IS(node, "AST_MUL") ||
      AST_TOKEN_IS(node, "AST_DIV")) {
    currentNode = OT_CreateNode(node, OT_OPERATION,
                                NULL, OT_ASTToOpToken(node->token));
    OT_AddChild(ot, currentNode);
  }
  else if (AST_TOKEN_IS(node, "AST_ASSIGNMENT")) {
    currentNode = OT_CreateNode(node, OT_OPERATION, NULL, __WRITE);
    OT_AddChild(ot, currentNode);
  }
  else if (AST_TOKEN_IS(node, "AST_VAR_DEC")) {
    currentNode = OT_CreateNode(node, OT_OPERATION, NULL, __WRITE);
    OT_AddChild(ot, currentNode);
  }
  else if (AST_TOKEN_IS(node, "AST_CALL")) {
    currentNode = OT_CreateNode(node, OT_OPERATION, NULL, __CALL);
    OT_AddChild(ot, currentNode);
  }
  else
  {
    printf("====> VISITING ELEMENT :: name: %s, id: %u\n",node->token, node->id);
    STE* variable = ST_Search(st, node->token, ST_VAR);
    if (variable) {
          currentNode = OT_CreateNode(node, OT_VARIABLE,
                                      variable->value.variable.name,
                                      variable->value.variable.type);
          OT_AddChild(ot, currentNode);
          OT_InsertBetween(ot, currentNode, OT_CreateAuxiliaryNode(OT_OPERATION, NULL, __READ));
    }
    STE* constant = ST_Search(st, node->token, ST_CONSTANT);
    if (constant) {
      currentNode = OT_CreateNode(node, OT_CONSTANT,
                                  constant->value.constant.value,
                                  constant->value.constant.type);
      OT_AddChild(ot, currentNode);
    }
  }
  for (int i = 0; i < node->childCount; i++)
    OT_Walker(currentNode, st, AST_GetChild(node, i));

}

void OT_TypeResolver(OT* ot) {
  if (!ot) return;

  for (int i = 0; i < ot->childCount; i++) {
    OT_TypeResolver(OT_GetChild(ot, i));
  }

  if (ot->childCount > 0) {
    int uniformType = 1;
    char* childType = NULL;

    OT* firstChild = OT_GetChild(ot, 0);
    switch (firstChild->dataType) {
      case OT_VARIABLE:
        childType = firstChild->data.variable.varType;
        break;
      case OT_OPERATION:
      case OT_FUNCTION:
        childType = firstChild->data.operation.returnType;
        break;
      case OT_CONSTANT:
        childType = firstChild->data.constant.constType;
        break;
      case OT_AUX:
        childType = firstChild->data.auxiliary.firstOption;
        break;
      default:
        uniformType = 0;
        break;
    }

    for (int i = 1; i < ot->childCount; i++) {
      OT* child = OT_GetChild(ot, i);
      char* currentChildType = NULL;

      switch (child->dataType) {
        case OT_VARIABLE:
          currentChildType = child->data.variable.varType;
          break;
        case OT_OPERATION:
        case OT_FUNCTION:
          currentChildType = child->data.operation.returnType;
          break;
        case OT_CONSTANT:
          currentChildType = child->data.constant.constType;
          break;
        case OT_AUX:
          currentChildType = child->data.auxiliary.firstOption;
          break;
        default:
          uniformType = 0;
          break;
      }

      if (!currentChildType || strcmp(currentChildType, childType) != 0) {
        uniformType = 0;
        break;
      }
    }

    if (uniformType && childType) {
      switch (ot->dataType) {
        case OT_OPERATION:
        case OT_FUNCTION:
          ot->data.operation.returnType = childType;
          break;
        case OT_VARIABLE:
          ot->data.variable.varType = childType;
          break;
        default:
          break;
      }
    }
  }
}




char* OT_ASTToOpToken(const char* astToken) {
  if (!astToken) {
    return "OT_TREE_ERROR_NODE";
  }
  char* prefix = "OP";
  char* underscore = strchr(astToken, '_');
  if (!underscore)
    return "OT_TREE_ERROR_NODE";

  size_t new_length = strlen(prefix) + strlen(underscore) + 1;

  char* otToken = (char*)safe_malloc(new_length);

  snprintf(otToken, new_length, "%s%s", prefix, underscore);

  return otToken;
}
