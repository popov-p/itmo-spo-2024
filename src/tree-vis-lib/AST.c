#include "AST.h"
#include "safe_mem.h"
#include <stdlib.h>
#include <stdint.h>

AST* AST_CreateNode(uint32_t id, char* token) {
  AST* node = (AST*)safe_malloc(sizeof(AST));
  node->parent = NULL;
  node->children = NULL;
  node->childCount = 0;
  node->id = id;
  node->token = strdup(token);
  return node;
}

void AST_AddChild(AST* parent, AST* child) {
  if (!parent) {
    AST_Free(child);
  }
  if (!child)
    return;

  parent->children = (AST**)safe_realloc(parent->children, sizeof(AST*) * (parent->childCount + 1));

  parent->childCount++;
  parent->children[parent->childCount-1] = child;
  child->parent = parent;
}

void AST_Free(AST* node) {
  if (!node)
    return;
  free(node->token);

  for (size_t i = 0; i < node->childCount; i++)
    AST_Free(node->children[i]);

  free(node->children);
  free(node);
}

AST* AST_FindNodeById(AST* node, uint32_t id) {
  if (!node)
    return NULL;
  if (node->id == id)
    return node;

  for (size_t i = 0; i < node->childCount; i++) {
    AST* foundNode = AST_FindNodeById(node->children[i], id);
    if (foundNode)
      return foundNode;
  }

  return NULL;
}

AST* AST_GetChild(AST* parent, size_t i) {
  if (!parent || i >= parent->childCount) {
    return NULL;
  }
  return parent->children[i];
}



void AST_InsertBetween(AST* parent,
                   AST* thatChild,
                   AST* thisNode) {
  if (!parent || !thatChild || !thisNode)
    return;

  if (thatChild->parent != parent)
    return;

  thisNode->children = (AST**)safe_malloc(sizeof(AST*));
  thisNode->children[0] = thatChild;
  thisNode->childCount = 1;
  thatChild->parent = thisNode;

  for (size_t i = 0; i < parent->childCount; i++) {
    if (parent->children[i] == thatChild) {
      parent->children[i] = thisNode;
      break;
    }
  }
  thisNode->parent = parent;
}

AST* AST_BuildFromParseResult(ParseResult* parseResult) {
  AST* head = AST_CreateNode(parseResult->p->adaptor->getUniqueID(parseResult->p->adaptor,
                                                              parseResult->sr.tree),
                         (char*)parseResult->sr.tree->getText(parseResult->sr.tree)->chars);

  int childCount = parseResult->sr.tree->getChildCount(parseResult->sr.tree);

  for(int i = 0; i < childCount; i++) {
    AST_SetChildFromAntlrNode(head, parseResult->p->adaptor,
                          parseResult->sr.tree->getChild(parseResult->sr.tree, i));
  }

  return head;
}

void AST_SetChildFromAntlrNode(AST* parent,
                           pANTLR3_BASE_TREE_ADAPTOR adaptor,
                           pANTLR3_BASE_TREE node) {
  if (!node)
    return;
  AST* child = AST_CreateNode(adaptor->getUniqueID(adaptor, node),
                          (char*)node->getText(node)->chars);
  AST_AddChild(parent, child);

  int childCount = node->getChildCount(node);
  for (int i = 0; i < childCount; i++) {
    pANTLR3_BASE_TREE child_node = node->getChild(node, i);
    AST_SetChildFromAntlrNode(child, adaptor, child_node);
  }
}

