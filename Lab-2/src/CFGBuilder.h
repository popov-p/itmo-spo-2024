#ifndef CFGBUILDER_H
#define CFGBUILDER_H

#include "Treebuilder.h"

typedef struct File {
    char* file_name;
    struct Function** functions;
    int function_count;
} File;

typedef struct Function {
    char* name;
    char* signature;
    struct CFG* cfg;
    char* source_file;
} Function;

typedef struct CFG {
    struct BasicBlock** blocks;
    int block_count;
} CFG;

void walk_tree(pANTLR3_BASE_TREE node);
void walk_parse_tree(pParseResult parseResult);

#endif
