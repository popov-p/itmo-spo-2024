#pragma once
#include "Functions.h"
#include "OT.h"
#include "AG.h"

#define PUSH push_addr

typedef struct ASMFW {
  AS* set;
  F* function;
} ASMFW; // ASM Function Wrapper
void ASM_GenerateListing(AS* set, F* function, FILE* listing);
void ASM_Walker(ASMFW* funcWrap, OT* node, FILE* listing);
