#ifndef EXITSTACK_H
#define EXITSTACK_H

typedef struct {
    int currentLevel;
} LoopLevelCounter;

LoopLevelCounter* createLoopLevelCounter();

void freeLoopLevelCounter(LoopLevelCounter* counter);

void enterLoop(LoopLevelCounter* counter);

void exitLoop(LoopLevelCounter* counter);

int getCurrentLoopLevel(LoopLevelCounter* counter);

#endif
