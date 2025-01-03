#pragma once
#include "AST.h"

typedef struct OT {
  char* token;
  char* type; /* */
  struct OT* parent;
  struct OT** children;
  int childCount;
  uint32_t id;
} OT;


OT* OT_CreateNode(const char* token);
void OT_AddChild(OT* parent, OT* child);
void OT_RemoveChild(OT* parent, OT* child);
void OT_InsertBetween(OT* parent, OT* thatChild, OT* thisNode);
OT* OT_BuildFromAST(AST* node);

OT* OT_GetChild(const OT* parent, int index);

void OT_Walker(OT* ot, AST* node);
void OT_TypeResolver(OT* ot);
void OT_Free(OT* node);


char* OT_ASTToOp(const char* astToken);
