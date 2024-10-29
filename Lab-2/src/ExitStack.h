#ifndef EXITSTACK_H
#define EXITSTACK_H

typedef struct LoopLevelEntry {
    int exitBlockIndex;
    int loopIndex;
    int breakDetected;
} LoopLevelEntry;

typedef struct LoopLevelStack {
    LoopLevelEntry* entries;
    int currentLevel;
    int capacity;
} LoopLevelStack;

LoopLevelStack* createLoopLevelStack(int initialCapacity);

void pushLoopEntry(LoopLevelStack* stack, int exitBlockIndex, int loopIndex);
LoopLevelEntry popLoopEntry(LoopLevelStack* stack);
LoopLevelEntry getCurrentLoopEntry(LoopLevelStack* stack);
LoopLevelEntry getLoopEntryAtLevel(LoopLevelStack* stack, int depth); /*depth = 0 текущий*/
#endif
