#ifndef HASHTREE_H
#define HASHTREE_H

#include "uthash.h"
#include <antlr3.h>

typedef struct {
    uint32_t uniqueID;
    pANTLR3_BASE_TREE node;
    UT_hash_handle hh;
} TreeNodeMap;

void addNodeToMap(uint32_t id, pANTLR3_BASE_TREE node);
pANTLR3_BASE_TREE getNodeByUniqueID(uint32_t id);
void traverseTree(pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE tree);

#endif
