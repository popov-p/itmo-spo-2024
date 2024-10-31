#include "ExitStack.h"

#include <stdio.h>
#include <stdlib.h>

LoopLevelStack* createLoopLevelStack(int initialCapacity) {
    LoopLevelStack* stack = malloc(sizeof(LoopLevelStack));
    stack->entries = malloc(sizeof(LoopLevelEntry) * 20);
    stack->currentLevel = -1;
    stack->capacity = initialCapacity;
    return stack;
}

void freeLoopLevelStack(LoopLevelStack* stack) {
    free(stack->entries);
    free(stack);
}

void pushLoopEntry(LoopLevelStack* stack, int exitBlockIndex, int loopIndex) {
    if (stack->currentLevel + 1 >= stack->capacity) {
        stack->capacity *= 2;
        stack->entries = (LoopLevelEntry*)realloc(stack->entries, stack->capacity * sizeof(LoopLevelEntry));
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

LoopLevelEntry getCurrentLoopEntry(LoopLevelStack* stack) {
    if (stack->currentLevel >= 0)
        return stack->entries[stack->currentLevel];
    else {
        fprintf(stderr, "LLS :: ERROR :: STACK EMPTY\n");
        return (LoopLevelEntry){-1, -1};
    }
}

LoopLevelEntry getLoopEntryAtLevel(LoopLevelStack* stack, int depth) {
    if (stack->currentLevel >= depth)
        return stack->entries[stack->currentLevel - depth];
    else {
        fprintf(stderr, "LLS :: ERROR :: STACK IS LESS THAN %d DEPTH\n", depth);
        return (LoopLevelEntry){-1, -1};
    }
}
