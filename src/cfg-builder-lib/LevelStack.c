#include "LevelStack.h"
#include <stdio.h>
#include <stdlib.h>
#include "safe_mem.h"

LoopLevelStack* createLoopLevelStack(int initialCapacity) {
  LoopLevelStack* stack = safe_malloc(sizeof(LoopLevelStack));
  stack->entries = safe_malloc(sizeof(LoopLevelEntry) * 20);
  stack->currentLevel = -1;
  stack->capacity = initialCapacity;
  return stack;
}

void freeLoopLevelStack(LoopLevelStack* stack) {
  if (!stack)
    return;
  if (stack->entries)
    free(stack->entries);
  free(stack);
}

void pushLoopEntry(LoopLevelStack* stack, int exitBlockIndex, int loopIndex) {
  if (stack->currentLevel + 1 >= stack->capacity) {
    stack->capacity *= 2;
    stack->entries = (LoopLevelEntry*)safe_realloc(stack->entries, stack->capacity * sizeof(LoopLevelEntry));
  }
  stack->currentLevel++;
  stack->entries[stack->currentLevel].exitBlockIndex = exitBlockIndex;
  stack->entries[stack->currentLevel].loopIndex = loopIndex;
  stack->entries[stack->currentLevel].breakDetected = 0;
}

LoopLevelEntry popLoopEntry(LoopLevelStack* stack) {
  if (stack->currentLevel >= 0) {
    LoopLevelEntry entry = stack->entries[stack->currentLevel];
    stack->currentLevel--;
    return entry;
  } else {
    fprintf(stderr, "LLS :: ERROR :: POPPING EMPTY STACK\n");
    return (LoopLevelEntry){-1, -1};
  }
}


IfLevelStack* createIfLevelStack(int capacity) {
  IfLevelStack* stack = (IfLevelStack*)safe_malloc(sizeof(IfLevelStack));

  stack->entries = (IfLevelEntry*)safe_malloc(capacity * sizeof(IfLevelEntry));

  stack->currentLevel = -1;
  stack->capacity = capacity;
  return stack;
}

void freeIfLevelStack(IfLevelStack* stack) {
  if (!stack) return;

  if (stack->entries)
    free(stack->entries);
  free(stack);
}

void pushIfEntry(IfLevelStack* stack,
                 int ifBlockIndex,
                 int elseBlockIndex,
                 int mergeBlockIndex) {
  if (stack->currentLevel + 1 >= stack->capacity) {
    stack->capacity *= 2;
    stack->entries = (IfLevelEntry*)safe_realloc(stack->entries,
                                                 stack->capacity * sizeof(IfLevelEntry));
  }
  stack->currentLevel++;
  stack->entries[stack->currentLevel].ifBlockIndex = ifBlockIndex;
  stack->entries[stack->currentLevel].elseBlockIndex = elseBlockIndex;
  stack->entries[stack->currentLevel].mergeBlockIndex = mergeBlockIndex;
}

IfLevelEntry popIfEntry(IfLevelStack* stack) {
  if (stack->currentLevel >= 0) {
    IfLevelEntry entry = stack->entries[stack->currentLevel];
    stack->currentLevel--;
    return entry;
  } else {
    fprintf(stderr, "ILS :: ERROR :: POPPING EMPTY STACK\n");
    return (IfLevelEntry){-1};
  }
}

