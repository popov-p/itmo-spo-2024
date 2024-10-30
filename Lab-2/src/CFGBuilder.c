#include "CFGBuilder.h"
#include "AST.h"
#include "CFGNodeProcessing.h"

void writeBlock(int num, FILE *file, enum BasicBlockType type) {
    if (type == standard)
        fprintf(file, "    node%d [label=\"BB%d\"];\n", num, num);
    if (type == merge)
        fprintf(file, "    node%d [label=\"MRG\"];\n", num);
    if (type == loop_exit)
        fprintf(file, "    node%d [label=\"LPXT\"];\n", num);
    if (type == repeat_exit)
        fprintf(file, "    node%d [label=\"RPXT\"];\n", num);
}

void writeCFGEdges(CFG* cfg, FILE *file) {
    for (int i = 0; i < cfg->blockCount; i++) {
        for(int j = 0; j < cfg->blocks[i]->successorCount; j++)
            fprintf(file, "    node%d -> node%d;\n", i, cfg->blocks[i]->successors[j]);
    }
}

CFG* generateCFG(AST* head) {
    CFG* cfg = initEmptyCFG();
    int lastBlockIndex = -1;
    cfgWalker(cfg, head, &lastBlockIndex);
    return cfg;
}

void outputCFG(CFG* cfg, FILE* file) {
    fprintf(file, "digraph G {\n");
    fprintf(file, "    rankdir=TB;\n");
    fprintf(file, "    start [label=\"%s\"];\n", "Начало");
    fprintf(file, "    end [label=\"%s\"];\n", "Конец");

    if(!cfg->blockCount) {
        fprintf(file, "    start -> end;\n");
        return;
    }

    for (int i = 0; i < cfg->blockCount; i++) {
        BasicBlock* bb = cfg->blocks[i];
        writeBlock(i, file, bb->bt);
    }

    writeCFGEdges(cfg, file);
    fprintf(file, "    start -> node%d;\n", 0);
    for (int i = 0; i < cfg->blockCount; i++) {
        BasicBlock* bb = cfg->blocks[i];
        if (!bb->successorCount)
            fprintf(file, "    node%d -> end;\n", i);
    }
    for (int i = 0; i < cfg->blockCount; i++)
        outputSubgraph(cfg, i, file);
    fprintf(file, "}\n");
}

File* createFile(const char* name) {
    File* file = malloc(sizeof(File));
 //Todo later
    file->fileName = strdup(name);
    file->functions = NULL;
    file->functionCount = 0;
    return file;
}
