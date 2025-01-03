#pragma once

typedef struct LE { // Индексы в массиве BB**.
  int exitBlockIndex;
  int loopIndex;
  int breakDetected;
} LE; //Loop Entry

typedef struct LS {
  LE* entries;
  int currentLevel;
  int capacity;
} LS; // Loop Stack

typedef struct IE { // Индексы в массиве BB**.
  int ifBlockIndex;
  int elseBlockIndex;
  int mergeBlockIndex;
} IE; // If Entry

typedef struct IS {
  IE* entries;
  int currentLevel;
  int capacity;
} IS; // If Stack


LS* LS_Create(int initialCapacity);
void LS_Free(LS* stack);
void LS_PushLE(LS* stack, int exitBlockIndex, int loopIndex);
LE LS_PopLE(LS* stack);


IS* IS_Create(int capacity);
void IS_Free(IS* stack);
void IS_PushIE(IS* stack, int ifBlockIndex, int elseBlockIndex, int mergeBlockIndex);
IE IS_PopIE(IS* stack);
