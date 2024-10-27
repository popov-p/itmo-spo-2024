#ifndef EXITSTACK_H
#define EXITSTACK_H

typedef struct LoopLevelStack {
    int* exitBlocks;
    int currentLevel;
    int capacity;
} LoopLevelStack;

LoopLevelStack* createLoopLevelStack();

void freeLoopLevelStack(LoopLevelStack* stack);

void pushExitBlock(LoopLevelStack* stack, int exitBlockIndex);

void popExitBlock(LoopLevelStack* stack);

int getCurrentExitBlock(LoopLevelStack* stack);

#endif
