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

void writeNode(pANTLR3_BASE_TREE tree, FILE *file, int* id) {
    fprintf(file, "    node%d [label=\"%s\"];\n", *id, (char *)tree->toString(tree)->chars); //NOLINT
}

void writeEdge(FILE *file, int* parentId, int* childId) {
    fprintf(file, "    node%d -> node%d;\n", *parentId, *childId); //NOLINT
}

void writeBlock(FILE *file, BasicBlock* block) {

}

void treeToDotNodes(pANTLR3_BASE_TREE node, FILE *file, int* id) {
    if (node == NULL) return;
    int current_id = ++(*id);
    pANTLR3_UINT8 debug_node_name = node->toString(node)->chars;
    printf("Visiting node: %s, text: %s\n", debug_node_name, (char*)node->getText(node)->chars);
    int childCount = node->getChildCount(node);
    writeNode(node, file, &current_id);
    for (int i = 0; i < childCount; i++) {
        treeToDotNodes(node->getChild(node, i), file, id);
    }
}

void treeToDotEdges(pANTLR3_BASE_TREE node, FILE *file, int* id) {
    if (node == NULL) return;
    if ((*id) == 0) {
        ++(*id); //root
    };
    int parent_id = *id;
    int childCount = node->getChildCount(node);

    for (int i = 0; i < childCount; i++) {
        pANTLR3_BASE_TREE childNode = node->getChild(node, i);
        (*id)++;
        int child_id = *id;

        writeEdge(file, &parent_id, &child_id);
        treeToDotEdges(childNode, file, id);
    }
}

void cfg_walker(CFG* cfg, pANTLR3_BASE_TREE node, FILE *file, int* id) {
    if (node == NULL) return;
    int current_id = ++(*id);
    pANTLR3_UINT8 debug_node_name = node->toString(node)->chars;
    printf("Visiting node: %s\n", debug_node_name);
    if (strcmp((char*)node->getText(node)->chars, "CALL") == 0) {
        addBasicBlock(cfg, createBasicBlock(current_id));
        printf("found CALL\n");
    }

    int childCount = node->getChildCount(node);
    for (int i = 0; i < childCount; i++) {
        cfg_walker(cfg, node->getChild(node, i), file, id);
    }
}

void generate_cfg(pANTLR3_BASE_TREE node, FILE *file) {
    CFG* cfg = createCFG();
    fprintf(file, "digraph G {\n"); //NOLINT
    int* id = (int*)malloc(sizeof(int)); //todo: encapsulate id into a cfg child count
    *id = 0;
    int start_id = *id;
    fprintf(file, "    node%d [label=\"%s\"];\n", *id, "Начало"); //NOLINT
    cfg_walker(cfg, node, file, id);
    int end_id = ++(*id);
    fprintf(file, "    node%d [label=\"%s\"];\n", (*id)++, "Конец"); //NOLINT
    writeEdge(file, &start_id, &end_id);
    fprintf(file, "}\n"); //NOLINT
}

void generate_cfg_from_CFG(FILE* file) {
    CFG* cfg = createCFG();
    fprintf(file, "digraph G {\n"); //NOLINT
    fprintf(file, "    node%d [label=\"%s\"];\n", 1, "Начало"); //NOLINT
    for (int i = 2; i < cfg->block_count; i++) {// assuming nodes Начало и Конец are already in CFG
        writeBlock(file, cfg->blocks[i]);
    }
    fprintf(file, "    node%d [label=\"%s\"];\n", 3, "Конец");
    fprintf(file, "}\n"); //NOLINT
}

void generate_parse_tree(pANTLR3_BASE_TREE tree, FILE *file) {
    fprintf(file, "digraph AST {\n"); //NOLINT
    fprintf(file, "    node [shape=box];\n"); //NOLINT

    int* id = (int*)malloc(sizeof(int));
    *id = 0;
    treeToDotNodes(tree, file, id);
    *id = 0;
    treeToDotEdges(tree, file, id);
    free(id);
    fprintf(file, "}\n"); //NOLINT
}

