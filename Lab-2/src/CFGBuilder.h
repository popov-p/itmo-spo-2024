#ifndef CFGBUILDER_H
#define CFGBUILDER_H

#include "TreeBuilder.h"
#include "BasicBlock.h"

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

void cfg_walker(CFG* cfg, AST* node, int* lastBlockIndex);
CFG* generateCFG(AST* head);
void outputCFG(CFG* cfg, FILE* file);
void writeBlock(int num, FILE *file);
void writeCFGEdges(CFG* cfg, FILE *file);
#endif
