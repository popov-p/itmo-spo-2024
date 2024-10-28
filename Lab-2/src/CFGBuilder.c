#include "CFGBuilder.h"
#include "AST.h"
#include "CFGNodeProcessing.h"

void writeBlock(int num, FILE *file, enum BasicBlockType type) {
    if (type == standard) {
        fprintf(file, "    node%d [label=\"BB%d\"];\n", num, num); //NOLINT
    }
    if (type == merge) {
        fprintf(file, "    node%d [label=\"MRG\"];\n", num); //NOLINT
    }
    if (type == loop_exit) {
        fprintf(file, "    node%d [label=\"LPXT\"];\n", num); //NOLINT
    }
    if (type == repeat_exit) {
        fprintf(file, "    node%d [label=\"RPXT\"];\n", num); //NOLINT
    }
}

void writeCFGEdges(CFG* cfg, FILE *file) {
    for (int i = 0; i < cfg->block_count; i++) {
        for(int j = 0; j < cfg->blocks[i]->successor_count; j++) {
            fprintf(file, "    node%d -> node%d;\n", i, cfg->blocks[i]->successors[j]); //NOLINT
        }
    }
}

CFG* generateCFG(AST* head) {
    CFG* cfg = initEmptyCFG();
    int* lastBlockIndex = (int*)malloc(sizeof(int));
    *lastBlockIndex = -1;
    cfgWalker(cfg, head, lastBlockIndex);
    free(lastBlockIndex);
    return cfg;
}

void outputCFG(CFG* cfg, FILE* file) {
    fprintf(file, "digraph G {\n"); //NOLINT
    fprintf(file, "    rankdir=TB;\n"); //NOLINT
    fprintf(file, "    start [label=\"%s\"];\n", "Начало"); //NOLINT
    fprintf(file, "    end [label=\"%s\"];\n", "Конец");

    if(cfg->block_count == 0) {
        fprintf(file, "    start -> end;\n");
        return;
    }

    for (int i = 0; i < cfg->block_count; i++) {
        BasicBlock* bb = cfg->blocks[i];
        writeBlock(i, file, bb->bt);
    }

    writeCFGEdges(cfg, file);
    fprintf(file, "    start -> node%d;\n", 0);
    for (int i = 0; i < cfg->block_count; i++) {
        BasicBlock* bb = cfg->blocks[i];
        if (bb->successor_count == 0) {
            fprintf(file, "    node%d -> end;\n", i);
        }
    }
    for (int i = 0; i < cfg->block_count; i++) {
        outputSubgraph(cfg, i, file);
    }
    fprintf(file, "}\n"); //NOLINT
}

File* createFile(const char* name) {
    File* file = malloc(sizeof(File));

    file->file_name = strdup(name);
    file->functions = NULL;
    file->function_count = 0;
    return file;
}
