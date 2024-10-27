#include "BasicBlock.h"
#include <stdlib.h>
#include <stdio.h>

BasicBlock* createBasicBlock(AST* node, enum BasicBlockType bt) {
    BasicBlock* block = (BasicBlock*)malloc(sizeof(BasicBlock));
    block->node = node;
    block->bt = bt;
    block->successors = NULL;
    block->successor_count = 0;
    return block;
}

void addSuccessor(BasicBlock* block, int successorIndex) {
    block->successor_count++;
    block->successors = (int*)realloc(block->successors, block->successor_count * sizeof(int));
    block->successors[block->successor_count - 1] = successorIndex;
}

void addBasicBlock(CFG* cfg, BasicBlock* block) {
    cfg->block_count++;
    cfg->blocks = (BasicBlock**)realloc(cfg->blocks, cfg->block_count * sizeof(BasicBlock*));
    cfg->blocks[cfg->block_count - 1] = block;
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
    }
}


CFG* initEmptyCFG() {
    CFG* cfg = (CFG*)malloc(sizeof(CFG));
    cfg->blocks = NULL;
    cfg->block_count = 0;
    cfg->processedNodes = createProcessedNodes(100);
    cfg->loopLevelCounter = createLoopLevelCounter();


    return cfg;
}

void freeCFG(CFG* cfg) {
    for (int i = 0; i < cfg->block_count; i++) {
        free(cfg->blocks[i]->successors);
        free(cfg->blocks[i]);
    }
    free(cfg->blocks);
    free(cfg);
}
