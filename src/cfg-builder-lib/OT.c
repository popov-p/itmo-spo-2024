#include <stdlib.h>
#include <string.h>
#include "OT.h"
#include "safe_mem.h"
#include "commands.h"

#define __READ  "__READ"
#define __WRITE  "__WRITE"
#define __PLACE "__PLACE"
#define __CONST "__CONST"
#define __HEAD__ "HEAD"

#define TOKEN_CONVERTS_TO_INT(node) ({            \
    char* endptr;                                 \
    strtol((node)->token, &endptr, 10);           \
    (*endptr == '\0');                            \
})

OT* OT_GetChild(const OT* parent, int index) {
  if (!parent || index < 0 || index >= parent->childCount)
    return NULL;
  return parent->children[index];
}

OT* OT_createNode(const char* token) {
  if(!token)
    return NULL;
  OT* node = (OT*)safe_malloc(sizeof(OT));
  node->token = strdup(token);
  node->returnType = NULL;
  node->parent = NULL;
  node->children = (OT**)safe_malloc(sizeof(OT*));
  node->childCount = 0;
  node->id = arc4random();
  return node;
}

void OT_addChild(OT* parent, OT* child) {
  parent->children = realloc(parent->children, (parent->childCount + 1) * sizeof(OT*));
  parent->children[parent->childCount] = child;
  parent->childCount++;

  child->parent = parent;
}

void OT_removeChild(OT* parent, OT* child) {
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

void OT_insertBetween(OT* parent,
                      OT* thatChild,
                      OT* thisNode) {
  if (!parent || !thatChild || !thisNode) return;

  OT_removeChild(parent, thatChild);
  OT_addChild(parent, thisNode);
  OT_addChild(thisNode, thatChild);
}

void OT_destroy(OT* node) {
  if (!node) return;

  free(node->token);
  if (node->children) {
    for (size_t i = 0; node->children[i]; i++) {
      OT_destroy(node->children[i]);
    }
    free(node->children);
  }
  free(node);
}

OT* OT_Assignment(AST* node) {
  if (!node) return NULL;
  OT* ot = OT_createNode(__HEAD__);
  OT_Walker(ot, node);

  return ot;
}

void OT_Walker(OT* ot, AST* node) {
  if (!node) return;

  OT* currentNode = NULL;

  if(TOKEN_CONVERTS_TO_INT(node)) {
    const char* substrings[] = {__CONST, ": ", node->token};
    currentNode = OT_createNode(concatenateStrings(3, substrings));
    OT_addChild(ot, currentNode);
  }

  else if (TOKEN_IS(node, "+") ||
           TOKEN_IS(node, "-") ||
           TOKEN_IS(node, "*") ||
           TOKEN_IS(node, "/")) {
    currentNode = OT_createNode(node->token);
    OT_addChild(ot, currentNode);
  }
  else if (TOKEN_IS(node, "ASSIGNMENT")) {
    currentNode = OT_createNode(__WRITE);
    OT_addChild(ot, currentNode);
  }
  else
  {
    const char* substrings[] = {__PLACE, ": ", node->token};
    currentNode = OT_createNode(concatenateStrings(3, substrings));
    OT_addChild(ot, currentNode);
    OT_insertBetween(ot, currentNode, OT_createNode(__READ));
  }
  for (int i = 0; i < node->childCount; i++)
    OT_Walker(currentNode, getChild(node, i));

}

void OT_TypeResolver(OT* ot) {
  if (!ot) return;
  for (int i = 0; i < ot->childCount; i++) {
    OT* child = OT_GetChild(ot, i);
    OT_TypeResolver(child);
  }
  // if()
}
