#include "CFGBuilder.h"

void walk_tree(pANTLR3_BASE_TREE node) {
    if (node == NULL) return;

    pANTLR3_UINT8 debug_node_name = node->toString(node)->chars;
    printf("Visiting node: %s\n", debug_node_name);

    int childCount = node->getChildCount(node);
    for (int i = 0; i < childCount; i++) {
        walk_tree(node->getChild(node, i));
    }
}

void walk_parse_tree(pParseResult parseResult) {
    if (parseResult == NULL || parseResult->sr.tree == NULL) return;
    walk_tree(parseResult->sr.tree);
}

