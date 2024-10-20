#include "OpTree.h"
#include "HashTree.h"

void writeNode(pANTLR3_BASE_TREE tree, uint32_t* id, int basicBlockIndex, FILE *file) {
    fprintf(file, "    cluster_%d_node%u [label=\"%s\"];\n", basicBlockIndex,
             *id, (char *)tree->toString(tree)->chars); //NOLINT
}

void writeEdge(uint32_t* parentId, uint32_t* childId, int basicBlockIndex, FILE *file) {
    fprintf(file, "    cluster_%d_node%u -> cluster_%d_node%u;\n",
            basicBlockIndex, *parentId, basicBlockIndex, *childId); //NOLINT
}

void outputOpNode(pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE node, int basicBlockIndex, FILE *file) {
    if (adaptor == NULL) return;
    if (node == NULL) return;

    char* name = (char*)adaptor->getText(adaptor, node)->chars;
    uint32_t current_id = adaptor->getUniqueID(adaptor, node);
    printf("Visiting node: %s\n", name);
    int childCount = node->getChildCount(node);

    writeNode(node, &current_id, basicBlockIndex, file);
    for (int i = 0; i < childCount; i++) {
        pANTLR3_BASE_TREE child = adaptor->getChild(adaptor, node, i);
        outputOpNode(adaptor, child, basicBlockIndex, file);
    }
}


void outputOpEdge(pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE node, int basicBlockIndex, FILE *file) {
    char* name = (char*)adaptor->getText(adaptor, node)->chars;
    uint32_t current_id = adaptor->getUniqueID(adaptor, node);
    printf("Visiting node: %s\n", name);
    //printf("current ID: %d")
    int childCount = node->getChildCount(node);

    for (int i = 0; i < childCount; i++) {
        pANTLR3_BASE_TREE childNode = node->getChild(node, i);
        uint32_t child_id = adaptor->getUniqueID(adaptor, childNode);

        writeEdge(&current_id, &child_id, basicBlockIndex, file);
        outputOpEdge(adaptor, childNode, basicBlockIndex, file);
    }
}

void outputSubgraph(pParseResult parseResult, CFG* cfg, int basicBlockIndex, FILE* file) {
    fprintf(file, "subgraph cluster_%d {\n", basicBlockIndex);
    fprintf(file, "    label=\"%s%d\";\n", "BB", basicBlockIndex);
    BasicBlock* bb = cfg->blocks[basicBlockIndex];
    pANTLR3_BASE_TREE node = getNodeByUniqueID(bb->id);
    outputOpNode(parseResult->p->adaptor, node, basicBlockIndex, file);
    outputOpEdge(parseResult->p->adaptor, node, basicBlockIndex, file);
    fprintf(file, "}\n");
}
