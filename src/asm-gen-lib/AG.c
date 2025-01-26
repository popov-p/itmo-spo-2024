#include "AG.h"
#include "safe_mem.h"

AG* AG_init(unsigned short start, unsigned short end) {
  AG* gen = (AG*)safe_malloc(sizeof(AG));
  if (gen) {
    gen->current = start;
    gen->end = end;
  }
  return gen;
}

bool AG_next(AG *gen, unsigned short *out) {
  if (gen->current < gen->end) {
    *out = gen->current++;
    return true;
  }
  return false;
}

bool AG_generateUniqueAddr(AS *set, unsigned short *out) {
  for (unsigned short addr = 0x0000; addr <= 0xFFFF; addr++) {
    if (!AS_containsAddr(set, addr)) {
      *out = addr;
      AS_addAddr(set, addr);
      return true;
    }
  }
  return false; // all adresses are captured
}

void AG_destroy(AG *gen) {
  free(gen);
}

