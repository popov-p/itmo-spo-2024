#include "ProcessedNodes.h"

ProcessedNodes* createProcessedNodes(int initialCapacity) {
    ProcessedNodes* p = malloc(sizeof(ProcessedNodes));
    if (!p)
        return NULL;
    p->nodes = malloc(sizeof(AST*) * initialCapacity);
    if (!p->nodes) {
        free(p);
        return NULL;
    }
    p->count = 0;
    p->capacity = initialCapacity;
    return p;
}


void freeProcessedNodes(ProcessedNodes* p) {
    free(p->nodes);
    free(p);
}

int isProcessed(ProcessedNodes* p, AST* node) {
    for (int i = 0; i < p->count; i++) {
        if (p->nodes[i] == node)
            return 1;
    }
    return 0;
}

void addProcessed(ProcessedNodes* p, AST* node) {
    if (p->count >= p->capacity) {
        p->capacity *= 2;
        p->nodes = realloc(p->nodes, sizeof(AST*) * p->capacity);
    }
    p->nodes[p->count++] = node;
}
