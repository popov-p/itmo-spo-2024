#include "CFGBuilder.h"

//void writeNode(pANTLR3_BASE_TREE tree, FILE *file, int* id) {
//    fprintf(file, "    node%d [label=\"%s\"];\n", *id, (char *)tree->toString(tree)->chars); //NOLINT
//}

//void writeEdge(FILE *file, int* parentId, int* childId) {
//    fprintf(file, "    node%d -> node%d;\n", *parentId, *childId); //NOLINT
//}

void writeBlock(FILE *file, int num) {
    fprintf(file, "    node%d [label=\"%d\"];\n", num, num); //NOLINT
}

//void writeCFGEdges(FILE *file, CFG* cfg) {
//    for (int i = 0; i < cfg->block_count; i++) {
//        for(int j = 0; i < cfg->blocks[i]->successor_count; j++) {
//            fprintf(file, "    node%d [label=\"%d\"];\n", cfg->blocks[i]->id, cfg->blocks[i]->successors[j]); //NOLINT
//        }
//    }
//}

void cfg_walker(CFG* cfg, pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE tree, int* lastBlockIndex) {
    if (adaptor == NULL) return;
    if (tree == NULL) return;

    char* name = (char*)adaptor->getText(adaptor, tree)->chars;
    printf("Visiting node: %s\n", (char*)name);

    int childCount = adaptor->getChildCount(adaptor, tree);
    for (int i = 0; i < childCount; i++) {
        pANTLR3_BASE_TREE child = adaptor->getChild(adaptor, tree, i);
        cfg_walker(cfg, adaptor, child, lastBlockIndex);
    }

    if (strcmp((char*)adaptor->getText(adaptor, tree)->chars, "CALL") == 0) {
        BasicBlock* block = createBasicBlock(adaptor->getUniqueID(adaptor, tree));
        addBasicBlock(cfg, block);
        int currentBlockIndex = cfg->block_count - 1;
        if (*lastBlockIndex != -1) {
            addSuccessor(cfg->blocks[*lastBlockIndex], currentBlockIndex);
        }
        *lastBlockIndex = currentBlockIndex;
        pANTLR3_BASE_TREE_ADAPTOR func_name_node = adaptor->getChild(adaptor, tree, 0);
        printf("found CALL: %s\n", func_name_node->getText(func_name_node, func_name_node)->chars);
    }

//    int childCount = adaptor->getChildCount(adaptor, tree);
//    for (int i = 0; i < childCount; i++) {
//        cfg_walker(cfg, adaptor, adaptor->getChild(adaptor, tree, i));
//    }
}

//void generate_cfg(pANTLR3_BASE_TREE node, FILE *file) {
//    CFG* cfg = createCFG();
//    fprintf(file, "digraph G {\n"); //NOLINT
//    int* id = (int*)malloc(sizeof(int)); //todo: encapsulate id into a cfg child count
//    *id = 0;
//    int start_id = *id;
//    fprintf(file, "    node%d [label=\"%s\"];\n", *id, "Начало"); //NOLINT
//    //cfg_walker(cfg, node, file, id);
//    int end_id = ++(*id);
//    fprintf(file, "    node%d [label=\"%s\"];\n", (*id)++, "Конец"); //NOLINT
//    writeEdge(file, &start_id, &end_id);
//    fprintf(file, "}\n"); //NOLINT
//}

//CFG* cfg_from_antlr_tree(pParseResult parseResult) {
//   CFG* cfg = createCFG();
//   cfg_walker(cfg, tree, id);
//   return cfg; //NOLINT
//}

CFG* generateCFG(pParseResult parseResult) {
    CFG* cfg = initEmptyCFG();
    int* lastBlockIndex = (int*)malloc(sizeof(int));
    *lastBlockIndex = -1;
    cfg_walker(cfg, parseResult->p->adaptor, parseResult->sr.tree, lastBlockIndex);
    free(lastBlockIndex);
    return cfg;

}

void outputCFG(CFG* cfg, FILE* file) {
    //CFG* cfg = cfg_from_antlr_tree(tree);
    fprintf(file, "digraph G {\n"); //NOLINT
    fprintf(file, "    start [label=\"%s\"];\n", "Начало"); //NOLINT
    fprintf(file, "    end [label=\"%s\"];\n", "Конец");


    for (int i = 0; i < cfg->block_count; i++) {
        writeBlock(file, i);
    }
    //writeCFGEdges(file, cfg);
    fprintf(file, "    start -> node%d;\n", cfg->blocks[0]->id);
    fprintf(file, "    node%d -> end;\n", cfg->blocks[cfg->block_count-1]->id);
    fprintf(file, "}\n"); //NOLINT
}

//void generate_parse_tree(pANTLR3_BASE_TREE tree, FILE *file) {
//    fprintf(file, "digraph AST {\n"); //NOLINT
//    fprintf(file, "    node [shape=box];\n"); //NOLINT

//    int* id = (int*)malloc(sizeof(int));
//    *id = 0;
//    treeToDotNodes(tree, file, id);
//    *id = 0;
//    treeToDotEdges(tree, file, id);
//    free(id);
//    fprintf(file, "}\n"); //NOLINT
//}

