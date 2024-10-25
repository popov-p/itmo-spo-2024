#include "CFGBuilder.h"
#include "AST.h"
#include "CFGNodeProcessing.h"

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

void cfg_walker(CFG* cfg, AST* node, int* lastBlockIndex) {
    if (node == NULL) return;

    char* name = node->token;
    printf("Visiting node: %s\n", (char*)name);

    int childCount = node->child_count;
    for (int i = 0; i < childCount; i++) {
        AST* child = getChild(node, i);
        cfg_walker(cfg, child, lastBlockIndex);
    }

    if (strcmp(node->token, "CALL") == 0) {
        BasicBlock* block = createBasicBlock(node);
        addBasicBlock(cfg, block);
        int currentBlockIndex = cfg->block_count - 1;
        if (*lastBlockIndex != -1) {
            addSuccessor(cfg->blocks[*lastBlockIndex], currentBlockIndex);
        }
        *lastBlockIndex = currentBlockIndex;
        char* func_name = getChild(node, 0)->token;
        printf("found CALL-BB: %s\n", func_name);
    }
}

CFG* generateCFG(AST* head) {
    CFG* cfg = initEmptyCFG();

    int* lastBlockIndex = (int*)malloc(sizeof(int));
    *lastBlockIndex = -1;
    cfg_walker(cfg, head, lastBlockIndex);
    free(lastBlockIndex);
    return cfg;
}

void outputCFG(CFG* cfg, FILE* file) {
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
        outputSubgraph(cfg, i, file);
    }
    fprintf(file, "}\n"); //NOLINT
}


