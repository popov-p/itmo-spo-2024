#pragma once
#include "AS.h"

typedef struct AG {
  unsigned short current;
  unsigned short end;
} AG; // Address Generator

AG* AG_init(unsigned short start, unsigned short end);

bool AG_next(AG *gen, unsigned short *out);
bool AG_generateUniqueAddr(AS *set, unsigned short *out);
void AG_destroy(AG *gen);
