#pragma once
#include "AST.h"

typedef enum {
  OT_CONST,
  OT_PLACE,
  OT_OPERATION
} OT_t;

typedef struct OT {
  OT_t type;
  struct OT* left;
  struct OT* right;
  struct OT** children;
  int childCount;
} OT;

OT* buildOT (AST* node);
