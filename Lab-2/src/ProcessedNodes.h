#ifndef PROCESSEDNODES_H
#define PROCESSEDNODES_H

#include "AST.h"

typedef struct {
    AST** nodes;
    int count;
    int capacity;
} ProcessedNodes;

ProcessedNodes* createProcessedNodes(int initialCapacity);

void freeProcessedNodes(ProcessedNodes* p);

int isProcessed(ProcessedNodes* p, AST* node);

void addProcessed(ProcessedNodes* p, AST* node);


#endif
