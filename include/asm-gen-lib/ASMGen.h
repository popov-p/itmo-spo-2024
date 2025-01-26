#pragma once
#include "Functions.h"
#include "OT.h"

#define PUSH push_addr

void ASM_GenerateListing(F* function, FILE* listing);
void ASM_Walker(OT* node, FILE* listing);
