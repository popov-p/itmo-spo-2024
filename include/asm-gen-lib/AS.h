#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_ADDR_COUNT 65536

typedef struct AS {
  uint16_t elements[MAX_ADDR_COUNT];
  size_t size;
} AS; // Address Set


AS* AS_init();
void AS_free(AS* set);
bool AS_containsAddr(const AS* set, uint16_t value);
bool AS_addAddr(AS *set, uint16_t value);
bool AS_removeAddr(AS *set, uint16_t value);
void AS_print(const AS *set);
