#include "CFGBuilder.h"
#include "OpTree.h"

void writeBlock(int num, FILE *file) {
    fprintf(file, "    node%d [label=\"BB%d\"];\n", num, num); //NOLINT
}

void writeCFGEdges(CFG* cfg, FILE *file) {
    for (int i = 0; i < cfg->block_count; i++) {
        for(int j = 0; j < cfg->blocks[i]->successor_count; j++) {
            fprintf(file, "    node%d -> node%d;\n", i, cfg->blocks[i]->successors[j]); //NOLINT
        }
    }
}

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
}

CFG* generateCFG(pParseResult parseResult) {
    CFG* cfg = initEmptyCFG();
    int* lastBlockIndex = (int*)malloc(sizeof(int));
    *lastBlockIndex = -1;
    cfg_walker(cfg, parseResult->p->adaptor, parseResult->sr.tree, lastBlockIndex);
    free(lastBlockIndex);
    return cfg;
}

void outputCFG(pParseResult parseResult, CFG* cfg, FILE* file) {
    fprintf(file, "digraph G {\n"); //NOLINT
    fprintf(file, "    rankdir=TB;\n"); //NOLINT
    fprintf(file, "    start [label=\"%s\"];\n", "Начало"); //NOLINT
    fprintf(file, "    end [label=\"%s\"];\n", "Конец");

    for (int i = 0; i < cfg->block_count; i++) {
        writeBlock(i, file);
    }

    writeCFGEdges(cfg, file);
    fprintf(file, "    start -> node%d;\n", 0);
    fprintf(file, "    node%d -> end;\n", cfg->block_count-1);
    for (int i = 0; i < cfg->block_count; i++) {
        outputSubgraph(parseResult, cfg, i, file);
    }

    fprintf(file, "}\n"); //NOLINT
}


