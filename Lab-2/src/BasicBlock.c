#include "BasicBlock.h"
#include <stdlib.h>
#include <stdio.h>

BasicBlock* createBasicBlock(AST* node, enum BasicBlockType bt) {
    BasicBlock* block = (BasicBlock*)malloc(sizeof(BasicBlock));
    block->node = node;
    block->bt = bt;
    block->successors = NULL;
    block->successorCount = 0;
    return block;
}

void addSuccessor(BasicBlock* block, int successorIndex) {
    block->successorCount++;
    block->successors = (int*)realloc(block->successors, block->successorCount * sizeof(int));
    block->successors[block->successorCount - 1] = successorIndex;
}

void addBasicBlock(CFG* cfg, BasicBlock* block) {
    cfg->blockCount++;
    cfg->blocks = (BasicBlock**)realloc(cfg->blocks, cfg->blockCount * sizeof(BasicBlock*));
    cfg->blocks[cfg->blockCount - 1] = block;
}

void outputSubgraph(CFG* cfg, int basicBlockIndex, FILE* file) {
    BasicBlock* bb = cfg->blocks[basicBlockIndex];
    if (!(bb->node == NULL)) {
        fprintf(file, "subgraph cluster_%d {\n", basicBlockIndex);
        fprintf(file, "    label=\"%s%d\";\n", "BB", basicBlockIndex);

        AST* op = analyzeOp(findNodeById(bb->node, bb->node->id));

        outputOpNode(op, basicBlockIndex, file);
        outputOpEdge(op, basicBlockIndex, file);
        fprintf(file, "}\n");
        free(op);
    }
}

CFG* initEmptyCFG() {
    CFG* cfg = (CFG*)malloc(sizeof(CFG));
    cfg->blocks = NULL;
    cfg->blockCount = 0;
    cfg->processedNodes = createProcessedNodes(100);
    cfg->loopLevelStack = createLoopLevelStack(20);


    return cfg;
}

void freeCFG(CFG* cfg) {
    for (int i = 0; i < cfg->blockCount; i++) {
        free(cfg->blocks[i]->successors);
        free(cfg->blocks[i]);
    }
    free(cfg->blocks);
    free(cfg);
}
