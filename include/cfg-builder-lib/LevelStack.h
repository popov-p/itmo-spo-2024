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

typedef struct IfLevelEntry { //индексы в массиве BasicBlocks
    int ifBlockIndex;
    int elseBlockIndex;
    int mergeBlockIndex;
} IfLevelEntry;

typedef struct IfLevelStack {
    IfLevelEntry* entries;
    int currentLevel;
    int capacity;
} IfLevelStack;


LoopLevelStack* createLoopLevelStack(int initialCapacity);
void freeLoopLevelStack(LoopLevelStack* stack);
void pushLoopEntry(LoopLevelStack* stack, int exitBlockIndex, int loopIndex);
LoopLevelEntry popLoopEntry(LoopLevelStack* stack);


IfLevelStack* createIfLevelStack(int capacity);
void freeIfLevelStack(IfLevelStack* stack);
void pushIfEntry(IfLevelStack* stack, int ifBlockIndex, int elseBlockIndex, int mergeBlockIndex);
IfLevelEntry popIfEntry(IfLevelStack* stack);
#endif
