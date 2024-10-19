#ifndef CFGBUILDER_H
#define CFGBUILDER_H

#include "Treebuilder.h"
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

void walk_tree(pANTLR3_BASE_TREE node);
void walk_parse_tree(pParseResult parseResult);
void generate_cfg(pANTLR3_BASE_TREE node, FILE* file);
void generate_cfg_from_CFG(FILE* file);
void generate_parse_tree(pANTLR3_BASE_TREE tree, FILE* file);
void cfg_walker(CFG* cfg, pANTLR3_BASE_TREE node, FILE* file, int* id);
void writeBlock(FILE *file, BasicBlock* block);
#endif
