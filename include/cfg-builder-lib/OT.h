#pragma once
#include "AST.h"

typedef struct OT {
  char* token;
  struct OT* left;
  struct OT* right;
  struct OT** children;
  int childCount;
} OT;


OT* createOTNode(const char* token);
int addOTChild(OT* parent, OT* child);
OT* otAssignment(AST* node);
OT* otWalker(OT* ot, AST* node);
