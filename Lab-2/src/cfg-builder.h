#ifndef CFGBUILDER_H
#define CFGBUILDER_H

#include <antlr3.h>

typedef struct File {
    char *file_name;
    struct Function **functions;
    int function_count;
} File;

typedef struct Function {
    char *name;
    char *signature;
    struct CFG *cfg;
    char *source_file;
} Function;

typedef struct CFG {
    struct BasicBlock **blocks;
    int block_count;
} CFG;

void walk_tree(pANTLR3_BASE_TREE tree) {
    if (tree == NULL) return;

    printf("Visiting node: %s\n", tree->toString(tree)->chars);

    int childCount = tree->getChildCount(tree);
    for (int i = 0; i < childCount; i++) {
        pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE) tree->getChild(tree, i);
        walk_tree(child);
    }
}


#endif
