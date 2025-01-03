#include <stdlib.h>
#include <string.h>
#include "OT.h"
#include "safe_mem.h"
// #include "commands.h"

#define __READ  "OP_READ"
#define __WRITE  "OP_WRITE"
#define __PLACE "OP_PLACE"
#define __CONST "OP_CONST"
#define __HEAD__ "OP_HEAD"

OT* OT_GetChild(const OT* parent, int index) {
  if (!parent || index < 0 || index >= parent->childCount)
    return NULL;
  return parent->children[index];
}

OT* OT_CreateNode(const char* token) {
  if(!token)
    return NULL;
  OT* node = (OT*)safe_malloc(sizeof(OT));
  node->token = strdup(token);
  node->type = NULL;
  node->parent = NULL;
  node->children = (OT**)safe_malloc(sizeof(OT*));
  node->childCount = 0;
  node->id = arc4random();
  return node;
}

void OT_AddChild(OT* parent, OT* child) {
  parent->children = realloc(parent->children, (parent->childCount + 1) * sizeof(OT*));
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

  free(node->token);
  if (node->children) {
    for (size_t i = 0; node->children[i]; i++) {
      OT_Free(node->children[i]);
    }
    free(node->children);
  }
  free(node);
}

OT* OT_BuildFromAST(AST* node) {
  if (!node) return NULL;
  OT* ot = OT_CreateNode(__HEAD__);
  OT_Walker(ot, node);

  return ot;
}



void OT_Walker(OT* ot, AST* node) {
  if (!node) return;

  OT* currentNode = NULL;

  // if(TOKEN_CONVERTS_TO_INT(node)) {
  //   const char* substrings[] = {__CONST, ": ", node->token};
  //   currentNode = OT_CreateNode(node->token/*concatenateStrings(3, substrings)*/);
  //   OT_AddChild(ot, currentNode);
  //  }

  if (TOKEN_IS(node, "AST_PLUS") ||
      TOKEN_IS(node, "AST_MINUS") ||
      TOKEN_IS(node, "AST_MUL") ||
      TOKEN_IS(node, "AST_DIV")) {
    currentNode = OT_CreateNode(OT_ASTToOp(node->token));
    OT_AddChild(ot, currentNode);
  }
  else if (TOKEN_IS(node, "AST_ASSIGNMENT")) {
    currentNode = OT_CreateNode(__WRITE);
    OT_AddChild(ot, currentNode);
  }
  else if (TOKEN_IS(node, "AST_VAR_DEC")) {
    currentNode = OT_CreateNode(__WRITE);
    OT_AddChild(ot, currentNode);
  }
  else
  {
    // const char* substrings[] = {__PLACE, ": ", node->token};
    currentNode = OT_CreateNode(node->token/*concatenateStrings(3, substrings)*/);
    OT_AddChild(ot, currentNode);
    OT_InsertBetween(ot, currentNode, OT_CreateNode(__READ));
  }
  for (int i = 0; i < node->childCount; i++)
    OT_Walker(currentNode, AST_GetChild(node, i));

}

void OT_TypeResolver(OT* ot) {
  if (!ot) return;
  // if(ot->)
  // STE* intConstEntry = ST_SearchByValue(st, node->token, INT_CONST);
}

char* OT_ASTToOp(const char* astToken) {
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
