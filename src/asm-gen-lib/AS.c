#include "AS.h"
#include "safe_mem.h"

AS* AS_init() {
  AS* set = (AS*)safe_malloc(sizeof(AS));
  if (set)
    set->size = 0;
  return set;
}

void AS_free(AS* set) {
  free(set);
}

bool AS_containsAddr(const AS* set, unsigned short value) {
  for (size_t i = 0; i < set->size; i++) {
    if (set->elements[i] == value) {
      return true;
    }
  }
  return false;
}

bool AS_addAddr(AS *set, unsigned short value) {
  if (AS_containsAddr(set, value)) {
    return false;
  }
  if (set->size >= MAX_ADDR_COUNT) {
    return false; // overflow
  }
  set->elements[set->size++] = value;
  return true;
}

bool AS_removeAddr(AS *set, unsigned short value) {
  for (size_t i = 0; i < set->size; i++) {
    if (set->elements[i] == value) {
      set->elements[i] = set->elements[--set->size];
      return true;
    }
  }
  return false;
}

void AS_print(const AS *set) {
  printf("Set contains: ");
  for (size_t i = 0; i < set->size; i++) {
    printf("0x%04X ", set->elements[i]);
  }
  printf("\n");
}
