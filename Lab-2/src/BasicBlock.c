#include "BasicBlock.h"
#include <stdlib.h>
#include <stdio.h>

BasicBlock* createBasicBlock(AST* node) {
    BasicBlock* block = (BasicBlock*)malloc(sizeof(BasicBlock));
    block->node = node;
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
    fprintf(file, "subgraph cluster_%d {\n", basicBlockIndex);
    fprintf(file, "    label=\"%s%d\";\n", "BB", basicBlockIndex);
    BasicBlock* bb = cfg->blocks[basicBlockIndex];
    //pANTLR3_BASE_TREE result = analyzeOp(parseResult, getNodeByUniqueID(bb->id));
    AST*  op = findNodeById(bb->node, bb->node->id);
    outputOpNode(op, basicBlockIndex, file);
    outputOpEdge(op, basicBlockIndex, file);
    fprintf(file, "}\n");
}


CFG* initEmptyCFG() {
    CFG* cfg = (CFG*)malloc(sizeof(CFG));
    cfg->blocks = NULL;
    cfg->block_count = 0;

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
