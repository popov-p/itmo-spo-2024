#include <stdlib.h>
#include <stdio.h>
#include <antlr3.h>

#include "CFGBuilder.h"

void writeNode(pANTLR3_BASE_TREE tree, FILE *file, int* id) {
    fprintf(file, "    node%d [label=\"%s\"];\n", *id, (char *)tree->toString(tree)->chars); //NOLINT
}

void writeEdge(FILE *file, int parentId, int childId) {
    fprintf(file, "    node%d -> node%d;\n", parentId, childId);
}

void treeToDot(pANTLR3_BASE_TREE node, FILE *file, int* id) {
    if (node == NULL) return;
    int current_id = ++(*id);
    pANTLR3_UINT8 debug_node_name = node->toString(node)->chars;
    printf("Visiting node: %s\n", debug_node_name);
    int childCount = node->getChildCount(node);
    writeNode(node, file, &current_id);
    for (int i = 0; i < childCount; i++) {
        treeToDot(node->getChild(node, i), file, id);
    }
}

void treeEdges(pANTLR3_BASE_TREE node, FILE *file, int* id) {
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

        writeEdge(file, parent_id, child_id);
        treeEdges(childNode, file, id);
    }
}


int main(int argc, char *argv[]) {
    char *inputText = readFileToString("../test.txt");

    if (inputText == NULL) {
        printf("not ok. failed reading from file\n");
    }

    pParseResult parseResult = parse(inputText);
    //walk_parse_tree(parseResult);

    const char* filename = "../src/tree.dot";
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Cannot open file");
        return -1;
    }


    // Начало файла в формате DOT
    fprintf(file, "digraph AST {\n"); //NOLINT
    fprintf(file, "    node [shape=box];\n"); //NOLINT

    // Рекурсивный вызов для корневого узла
    int* id = (int*)malloc(sizeof(int));
    *id = 0;
    treeToDot(parseResult->sr.tree, file, id);
    *id = 0;
    treeEdges(parseResult->sr.tree, file, id);
    free(id);
    // Конец файла
    fprintf(file, "}\n"); //NOLINT
    fclose(file);
    return 0;
}

