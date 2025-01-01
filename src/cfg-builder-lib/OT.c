#include "OT.h"
#include "AST.h"
#include "safe_mem.h"

OT* createOTNode(const char* token) {
  OT* node = (OT*)safe_malloc(sizeof(OT));

  node->token = token ? strdup(token) : NULL;
  node->left = NULL;
  node->right = NULL;
  node->children = NULL;
  node->childCount = 0;

  return node;
}


int addOTChild(OT* parent, OT* child) {
  if (!parent || !child) {
    return -1;
  }

  OT** newChildren = (OT**)safe_realloc(parent->children, sizeof(OT*) * (parent->childCount + 1));

  parent->children = newChildren;
  parent->children[parent->childCount] = child;
  parent->childCount++;

  return 0;
}

void freeOT(OT* node) {
  if (!node) return;

  if (node->token)
    free(node->token);

  freeOT(node->left);
  freeOT(node->right);

  if (node->children) {
    for (int i = 0; i < node->childCount; i++)
      freeOT(node->children[i]);
    free(node->children);
  }

  free(node);
}


OT* otWalker(OT* ot, AST* node) {
  return NULL;
  for (int i = 0; i < node->childCount; i++)
    otWalker(ot, getChild(node, i));
}

OT* otAssignment(AST* node) {
  OT* head = otWalker(NULL, node);
  return head;
}

// void outputOpNode(AST* node, int basicBlockIndex, FILE *file) {
//   if (!node) return;

//   int childCount = node->childCount;

//   writeNode(node, basicBlockIndex, file);
//   for (int i = 0; i < childCount; i++) {
//     AST* child = getChild(node, i);
//     outputOpNode(child, basicBlockIndex, file);
//   }
// }

// void outputOpEdge(AST* parent, int basicBlockIndex, FILE *file) {
//   if(!parent)
//     return;
//   int childCount = parent->childCount;

//   for (int i = 0; i < childCount; i++) {
//     AST* child = getChild(parent, i);

//     writeEdge(parent, child, basicBlockIndex, file);
//     outputOpEdge(child, basicBlockIndex, file);
//   }
// }

// void analyzeCutCondition(AST* head) {
//   AST* condition = getChild(head, 0);
//   AST* leftOperand = getChild(condition, 0);
//   AST* valuePlaceQualifier = createNode(arc4random(), "__read");
//   insertBetween(condition, leftOperand, valuePlaceQualifier);
//   for (size_t i = 1; i < condition->childCount; i++) {
//     AST* element = getChild(condition, i);
//     AST* readQualifier = createNode(arc4random(), "__read");
//     insertBetween(condition, element, readQualifier);
//   }

// }

// void analyzeIf(AST* ifNode) {
//   if (ifNode->childCount < 2)
//     return;
//   analyzeCutCondition(ifNode);
// }

// void analyzeLoop(AST* loopNode) {
//   if (!loopNode)
//     return;

//   analyzeCutCondition(loopNode);
// }

// void analyzeRepeat(AST* repeatNode) {
//   if (!repeatNode)
//     return;
//   analyzeCutCondition(repeatNode);
// }

// void analyzeAssign(AST* assignNode) {
//   AST* lvalue = getChild(assignNode, 0);
//   AST* rvalue = getChild(assignNode, 1);
//   AST* vp = createNode(arc4random(), "__value_place");
//   AST* read = createNode(arc4random(), "__read");

//   insertBetween(assignNode, lvalue, vp);
//   insertBetween(assignNode, rvalue, read);
// }

// void analyzeCall(AST* call) {
//   if (strcmp(call->token, "CALL")) {
//     return;
//   }

//   if(call->childCount > 1) {
//     AST* list_expr = getChild(call, 1);
//     for (size_t i = 0; i < list_expr->childCount; i++) {
//       AST* listChild = getChild(list_expr, i);
//       if (listChild != NULL) {
//         AST* read = createNode(arc4random(), "__read");
//         insertBetween(list_expr, listChild, read);
//         analyzeCall(listChild);
//       }
//     }
//   }
// }

// OT* analyzeOp (AST* node) {
//   if(!node) //merge block or another service blocks
//     return NULL;
//   AST* head = NULL;
//   if(!strcmp(node->token, "CALL")) {
//     head = duplicateLeftSubtree(node);
//     analyzeCall(head);
//   }
//   if(!strcmp(node->token, "IF")) {
//     head = duplicateLeftSubtree(node);
//     analyzeIf(head);
//   }
//   if(!strcmp(node->token, "ELSE")) {
//     head = duplicateTree(node);
//   }
//   if(!strcmp(node->token, "LOOP")) {
//     head = duplicateLeftSubtree(node);
//     analyzeLoop(head);
//   }
//   if(!strcmp(node->token, "REPEAT")) {
//     head = duplicateRightSubtree(node);
//     analyzeRepeat(head);
//   }
//   if(!strcmp(node->token, "VAR_DEF")) {
//     head = duplicateTree(node);
//   }

//   if(!strcmp(node->token, "VAR_DEC")) {
//     head = duplicateTree(node);
//   }
//   if(!strcmp(node->token, "ASSIGNMENT")) {
//     head = duplicateTree(node);
//     analyzeAssign(head);
//   }
//   return head;
// }



// void outputOpNode(AST* node, int basicBlockIndex, FILE *file) {
//   if (!node) return;

//   int childCount = node->childCount;

//   writeNode(node, basicBlockIndex, file);
//   for (int i = 0; i < childCount; i++) {
//     AST* child = getChild(node, i);
//     outputOpNode(child, basicBlockIndex, file);
//   }
// }

// void outputOpEdge(AST* parent, int basicBlockIndex, FILE *file) {
//   if(!parent)
//     return;
//   int childCount = parent->childCount;

//   for (int i = 0; i < childCount; i++) {
//     AST* child = getChild(parent, i);

//     writeEdge(parent, child, basicBlockIndex, file);
//     outputOpEdge(child, basicBlockIndex, file);
//   }
// }

// void analyzeCutCondition(AST* head) {
//   AST* condition = getChild(head, 0);
//   AST* leftOperand = getChild(condition, 0);
//   AST* valuePlaceQualifier = createNode(arc4random(), "__read");
//   insertBetween(condition, leftOperand, valuePlaceQualifier);
//   for (size_t i = 1; i < condition->childCount; i++) {
//     AST* element = getChild(condition, i);
//     AST* readQualifier = createNode(arc4random(), "__read");
//     insertBetween(condition, element, readQualifier);
//   }

// }

// void analyzeIf(AST* ifNode) {
//   if (ifNode->childCount < 2)
//     return;
//   //analyzeCutCondition(ifNode);
// }

// void analyzeLoop(AST* loopNode) {
//   if (!loopNode)
//     return;

//   //analyzeCutCondition(loopNode);
// }

// void analyzeRepeat(AST* repeatNode) {
//   if (!repeatNode)
//     return;
//   // analyzeCutCondition(repeatNode);
// }

// void analyzeAssign(AST* assignNode) {
//   // * lvalue = getChild(assignNode, 0);
//   // AST* rvalue = getChild(assignNode, 1);
//   // AST* vp = createNode(arc4random(), "__value_place");
//   // AST* read = createNode(arc4random(), "__read");

//   // insertBetween(assignNode, lvalue, vp);
//   // insertBetween(assignNode, rvalue, read);
// }

// void analyzeCall(AST* call) {
//   if (strcmp(call->token, "CALL")) {
//     return;
//   }

//   if(call->childCount > 1) {
//     AST* list_expr = getChild(call, 1);
//     for (size_t i = 0; i < list_expr->childCount; i++) {
//       AST* listChild = getChild(list_expr, i);
//       if (listChild != NULL) {
//         AST* read = createNode(arc4random(), "__read");
//         insertBetween(list_expr, listChild, read);
//         analyzeCall(listChild);
//       }
//     }
//   }
// }

// OT* buildOT (AST* node) {
//   if(!node) //merge block or another service blocks
//     return NULL;
//   OT* head = NULL;
//   if(!strcmp(node->token, "CALL")) {
//     head = duplicateLeftSubtree(node);
//     analyzeCall(head);
//   }
//   if(!strcmp(node->token, "IF")) {
//     head = duplicateLeftSubtree(node);
//     analyzeIf(head);
//   }
//   if(!strcmp(node->token, "ELSE")) {
//     head = duplicateTree(node);
//   }
//   if(!strcmp(node->token, "LOOP")) {
//     head = duplicateLeftSubtree(node);
//     analyzeLoop(head);
//   }
//   if(!strcmp(node->token, "REPEAT")) {
//     head = duplicateRightSubtree(node);
//     analyzeRepeat(head);
//   }
//   if(!strcmp(node->token, "VAR_DEF")) {
//     head = duplicateTree(node);
//   }

//   if(!strcmp(node->token, "VAR_DEC")) {
//     head = duplicateTree(node);
//   }
//   if(!strcmp(node->token, "ASSIGNMENT")) {
//     head = duplicateTree(node);
//     analyzeAssign(head);
//   }
//   return head;
// }
