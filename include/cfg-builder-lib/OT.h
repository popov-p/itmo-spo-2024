#pragma once
#include "AST.h"

typedef struct OT {
  char* token;
  char* returnType; /* */
  struct OT* parent;
  struct OT** children;
  int childCount;
  uint32_t id;
} OT;


OT* OT_createNode(const char* token);
void OT_addChild(OT* parent, OT* child);
void OT_removeChild(OT* parent, OT* child);
void OT_insertBetween(OT* parent, OT* thatChild, OT* thisNode);
OT* OT_Assignment(AST* node);

OT* OT_GetChild(const OT* parent, int index);

void OT_Walker(OT* ot, AST* node);
void OT_TypeResolver(OT* ot);
void OT_destroy(OT* node);
