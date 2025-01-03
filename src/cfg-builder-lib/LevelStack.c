#include "LevelStack.h"
#include <stdio.h>
#include <stdlib.h>
#include "safe_mem.h"

LS* LS_Create(int initialCapacity) {
  LS* stack = safe_malloc(sizeof(LS));
  stack->entries = safe_malloc(sizeof(LE) * 20);
  stack->currentLevel = -1;
  stack->capacity = initialCapacity;
  return stack;
}

void LS_Free(LS* stack) {
  if (!stack)
    return;
  if (stack->entries)
    free(stack->entries);
  free(stack);
}

void LS_PushLE(LS* stack, int exitBlockIndex, int loopIndex) {
  if (stack->currentLevel + 1 >= stack->capacity) {
    stack->capacity *= 2;
    stack->entries = (LE*)safe_realloc(stack->entries, stack->capacity * sizeof(LE));
  }
  stack->currentLevel++;
  stack->entries[stack->currentLevel].exitBlockIndex = exitBlockIndex;
  stack->entries[stack->currentLevel].loopIndex = loopIndex;
  stack->entries[stack->currentLevel].breakDetected = 0;
}

LE LS_PopLE(LS* stack) {
  if (stack->currentLevel >= 0) {
    LE entry = stack->entries[stack->currentLevel];
    stack->currentLevel--;
    return entry;
  } else {
    fprintf(stderr, "LLS :: ERROR :: POPPING EMPTY STACK\n");
    return (LE){-1, -1, -1};
  }
}

IS* IS_Create(int capacity) {
  IS* stack = (IS*)safe_malloc(sizeof(IS));

  stack->entries = (IE*)safe_malloc(capacity * sizeof(IE));

  stack->currentLevel = -1;
  stack->capacity = capacity;
  return stack;
}

void IS_Free(IS* stack) {
  if (!stack) return;

  if (stack->entries)
    free(stack->entries);
  free(stack);
}

void IS_PushIE(IS* stack,
               int ifBlockIndex,
               int elseBlockIndex,
               int mergeBlockIndex) {
  if (stack->currentLevel + 1 >= stack->capacity) {
    stack->capacity *= 2;
    stack->entries = (IE*)safe_realloc(stack->entries,
                                       stack->capacity * sizeof(IE));
  }
  stack->currentLevel++;
  stack->entries[stack->currentLevel].ifBlockIndex = ifBlockIndex;
  stack->entries[stack->currentLevel].elseBlockIndex = elseBlockIndex;
  stack->entries[stack->currentLevel].mergeBlockIndex = mergeBlockIndex;
}

IE IS_PopIE(IS* stack) {
  if (stack->currentLevel >= 0) {
    IE entry = stack->entries[stack->currentLevel];
    stack->currentLevel--;
    return entry;
  } else {
    fprintf(stderr, "ILS :: ERROR :: POPPING EMPTY STACK\n");
    return (IE){-1, -1, -1};
  }
}

