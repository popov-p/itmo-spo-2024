#include "AST.h"
#include "safe_mem.h"
#include <stdlib.h>
#include <stdint.h>

AST* createNode(uint32_t id, char* token) {
  AST* node = (AST*)safe_malloc(sizeof(AST));
  node->parent = NULL;
  node->children = NULL;
  node->childCount = 0;
  node->id = id;
  node->token = strdup(token);
  return node;
}

void addChild(AST* parent, AST* child) {
  if (!parent) {
    freeAST(child);
  }
  if (!child)
    return;

  parent->children = (AST**)safe_realloc(parent->children, sizeof(AST*) * (parent->childCount + 1));

  parent->childCount++;
  parent->children[parent->childCount-1] = child;
  child->parent = parent;
}

void freeAST(AST* node) {
  if (!node)
    return;
  free(node->token);

  for (size_t i = 0; i < node->childCount; i++)
    freeAST(node->children[i]);

  free(node->children);
  free(node);
}

AST* findNodeById(AST* node, uint32_t id) {
  if (!node)
    return NULL;
  if (node->id == id)
    return node;

  for (size_t i = 0; i < node->childCount; i++) {
    AST* foundNode = findNodeById(node->children[i], id);
    if (foundNode)
      return foundNode;
  }

  return NULL;
}

AST* getChild(AST* parent, size_t i) {
  if (!parent || i >= parent->childCount) {
    return NULL;
  }
  return parent->children[i];
}



void insertBetween(AST* parent,
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

AST* buildFromParseResult(ParseResult* parseResult) {
  AST* head = createNode(parseResult->p->adaptor->getUniqueID(parseResult->p->adaptor,
                                                              parseResult->sr.tree),
                         (char*)parseResult->sr.tree->getText(parseResult->sr.tree)->chars);

  int childCount = parseResult->sr.tree->getChildCount(parseResult->sr.tree);

  for(int i = 0; i < childCount; i++) {
    setChildFromAntlrNode(head, parseResult->p->adaptor,
                          parseResult->sr.tree->getChild(parseResult->sr.tree, i));
  }

  return head;
}

void setChildFromAntlrNode(AST* parent,
                           pANTLR3_BASE_TREE_ADAPTOR adaptor,
                           pANTLR3_BASE_TREE node) {
  if (!node)
    return;
  AST* child = createNode(adaptor->getUniqueID(adaptor, node),
                          (char*)node->getText(node)->chars);
  addChild(parent, child);

  int childCount = node->getChildCount(node);
  for (int i = 0; i < childCount; i++) {
    pANTLR3_BASE_TREE child_node = node->getChild(node, i);
    setChildFromAntlrNode(child, adaptor, child_node);
  }
}

