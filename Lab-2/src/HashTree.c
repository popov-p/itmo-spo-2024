#include "HashTree.h"

TreeNodeMap* nodeMap = NULL;

void addNodeToMap(uint32_t id, pANTLR3_BASE_TREE node) {
    TreeNodeMap* entry = (TreeNodeMap*)malloc(sizeof(TreeNodeMap));
    entry->uniqueID = id;
    entry->node = node;

    HASH_ADD_INT(nodeMap, uniqueID, entry); //NOLINT
}

pANTLR3_BASE_TREE getNodeByUniqueID(uint32_t id) {
    TreeNodeMap* entry = NULL;
    HASH_FIND_INT(nodeMap, &id, entry);

    return entry ? entry->node : NULL;
}


void traverseTree(pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE tree) {
    if (adaptor == NULL || tree == NULL) return;

    uint32_t id = adaptor->getUniqueID(adaptor, tree);

    addNodeToMap(id, tree);

    int childCount = adaptor->getChildCount(adaptor, tree);
    for (int i = 0; i < childCount; i++) {
        pANTLR3_BASE_TREE child = adaptor->getChild(adaptor, tree, i);
        traverseTree(adaptor, child);
    }
}
