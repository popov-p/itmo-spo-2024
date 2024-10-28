#ifndef EXITSTACK_H
#define EXITSTACK_H

typedef struct LoopLevelEntry {
    int exitBlockIndex;
    int loopIndex;
} LoopLevelEntry;

typedef struct LoopLevelStack {
    LoopLevelEntry* entries;
    int currentLevel;
    int capacity;
} LoopLevelStack;

LoopLevelStack* createLoopLevelStack();

void pushLoopEntry(LoopLevelStack* stack, int exitBlockIndex, int loopIndex);
LoopLevelEntry popLoopEntry(LoopLevelStack* stack);
LoopLevelEntry getCurrentLoopEntry(LoopLevelStack* stack);





#endif
