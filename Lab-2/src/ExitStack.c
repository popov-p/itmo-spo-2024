#include "ExitStack.h"

#include <stdio.h>
#include <stdlib.h>


LoopLevelCounter* createLoopLevelCounter() {
    LoopLevelCounter* counter = (LoopLevelCounter*)malloc(sizeof(LoopLevelCounter));
    counter->currentLevel = 0;
    return counter;
}

void freeLoopLevelCounter(LoopLevelCounter* counter) {
    free(counter);
}

void enterLoop(LoopLevelCounter* counter) {
    counter->currentLevel++;
}

void exitLoop(LoopLevelCounter* counter) {
    if (counter->currentLevel > 0) {
        counter->currentLevel--;
    } else {
        fprintf(stderr, "Error: Exiting from a non-existent loop level.\n");
    }
}

int getCurrentLoopLevel(LoopLevelCounter* counter) {
    return counter->currentLevel;
}
