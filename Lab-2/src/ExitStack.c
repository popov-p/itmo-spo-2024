#include "ExitStack.h"

#include <stdio.h>
#include <stdlib.h>

LoopLevelStack* createLoopLevelStack() {
    LoopLevelStack* stack = malloc(sizeof(LoopLevelStack));
    stack->entries = malloc(sizeof(LoopLevelEntry) * 20);
    stack->currentLevel = 0;
    stack->capacity = 20;
    return stack;
}

void freeLoopLevelStack(LoopLevelStack* stack) {
    free(stack->entries);
    free(stack);
}

void pushLoopEntry(LoopLevelStack* stack, int exitBlockIndex, int loopIndex) {
    if (stack->currentLevel >= stack->capacity) {
        stack->capacity *= 2;
        stack->entries = (LoopLevelEntry*)realloc(stack->entries, stack->capacity * sizeof(LoopLevelEntry));
    }
    stack->entries[stack->currentLevel].exitBlockIndex = exitBlockIndex;
    stack->entries[stack->currentLevel].loopIndex = loopIndex;
    stack->currentLevel++;
}

LoopLevelEntry popLoopEntry(LoopLevelStack* stack) {
    if (stack->currentLevel > 0) {
        stack->currentLevel--;
        return stack->entries[stack->currentLevel];
    } else {
        fprintf(stderr, "Error: Popping from an empty loop level stack.\n");
        return (LoopLevelEntry){-1, -1};
    }
}

LoopLevelEntry getCurrentLoopEntry(LoopLevelStack* stack) {
    if (stack->currentLevel > 0) {
        return stack->entries[stack->currentLevel - 1];
    } else {
        fprintf(stderr, "Error: No current loop entry in an empty loop level stack.\n");
        return (LoopLevelEntry){-1, -1};
    }
}

LoopLevelEntry getLoopEntryAtLevel(LoopLevelStack* stack, int depth) { /*depth = 0 текущий*/
    if (stack->currentLevel > depth) {
        return stack->entries[stack->currentLevel - 1 - depth];
    } else {
        fprintf(stderr, "Error: No loop entry at level %d in the loop level stack.\n", depth);
        return (LoopLevelEntry){-1, -1};
    }
}
