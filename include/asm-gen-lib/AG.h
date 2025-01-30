#pragma once
#include "AS.h"

typedef struct AG {
  uint16_t current;
  uint16_t end;
} AG; // Address Generator

AG* AG_init(uint16_t start, uint16_t end);

bool AG_next(AG *gen, uint16_t *out);
bool AG_nextUnique(AS *set, uint16_t *out);
void AG_destroy(AG *gen);
