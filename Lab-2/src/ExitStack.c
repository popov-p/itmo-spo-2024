#include "ExitStack.h"

#include <stdio.h>
#include <stdlib.h>

LoopLevelStack* createLoopLevelStack() {
    LoopLevelStack* stack = (LoopLevelStack*)malloc(sizeof(LoopLevelStack));
    stack->capacity = 20;
    stack->currentLevel = 0;
    stack->exitBlocks = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

void freeLoopLevelStack(LoopLevelStack* stack) {
    free(stack->exitBlocks);
    free(stack);
}

void pushExitBlock(LoopLevelStack* stack, int exitBlockIndex) {
    if (stack->currentLevel + 1 >= stack->capacity) {
        stack->capacity *= 2;
        stack->exitBlocks = (int*)realloc(stack->exitBlocks, stack->capacity * sizeof(int));
    }
    stack->currentLevel++;
    stack->exitBlocks[stack->currentLevel] = exitBlockIndex;
}

void popExitBlock(LoopLevelStack* stack) {
    if (stack->currentLevel > 0) {
        stack->currentLevel--;
    } else {
        fprintf(stderr, "Error: Popping from an empty loop level stack.\n");
    }
}

int getCurrentExitBlock(LoopLevelStack* stack) {
    if (stack->currentLevel > 0) {
        return stack->exitBlocks[stack->currentLevel];
    } else {
        fprintf(stderr, "Error: No current exit block in an empty loop level stack.\n");
        return -1;
    }
}

