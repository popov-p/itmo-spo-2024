#ifndef CFGBUILDER_H
#define CFGBUILDER_H

#include "TreeBuilder.h"
#include "BasicBlock.h"
#include "HashTree.h"

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

void cfg_walker(CFG* cfg, pANTLR3_BASE_TREE_ADAPTOR node, pANTLR3_BASE_TREE tree, int* lastBlockIndex);
CFG* generateCFG(pParseResult parseResult);
void outputCFG(CFG* cfg, FILE* file);
void outputOpTree(int basicBlockIndex, FILE* file);
void writeBlock(int num, FILE *file);
void writeCFGEdges(CFG* cfg, FILE *file);
//void writeBlock(FILE *file, BasicBlock* block);
#endif
