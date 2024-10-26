#ifndef CFGBUILDER_H
#define CFGBUILDER_H

#include "TreeBuilder.h"
#include "BasicBlock.h"
#include "ProcessedNodes.h"

typedef struct File {
    char* file_name;
    struct Function** functions;
    int function_count;
} File;

typedef struct Function {
    char* name;
    char* signature;
    CFG* cfg;
    char* source_file;
} Function;

void cfg_walker(CFG* cfg, AST* node, int* lastBlockIndex, ProcessedNodes* processedNodes);
CFG* generateCFG(AST* head);
void outputCFG(CFG* cfg, FILE* file);
void writeBlock(int num, FILE *file, enum BasicBlockType type);
void writeCFGEdges(CFG* cfg, FILE *file);
#endif
