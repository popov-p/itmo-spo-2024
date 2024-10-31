#include "CG.h"

CG* initEmptyCG(FunctionList* declaredFunctions) {
    CG* cg = (CG*)malloc(sizeof(CG));
    if (!cg) {
        fprintf(stderr, "ERROR :: MALLOC FAILED\n");
        return NULL;
    }

    cg->blocks = NULL;
    cg->blockCount = 0;

    return cg;
}

void freeCG(CG* cg) {
    if (!cg) return;

    for (int i = 0; i < cg->blockCount; ++i) {
        if (cg->blocks[i]) {
            free(cg->blocks[i]->successors);
            free(cg->blocks[i]);
        }
    }

    free(cg->blocks);
    free(cg);
}

CGB* createCallGraphBlock(AST* node) {
    CGB* block = (CGB*)malloc(sizeof(CGB));
    if (!block) {
        fprintf(stderr, "ERROR :: MALLOC FAILED\n");
        return NULL;
    }
    block->node = node;
    block->successors = NULL;
    block->successorCount = 0;
    return block;
}
void addCallGraphBlock(CG* cg, CGB* block) {
    cg->blocks = (CGB**)realloc(cg->blocks, (cg->blockCount + 1) * sizeof(CGB*));
    if (!cg->blocks) {
        fprintf(stderr, "ERROR :: REALLOC FAILED\n");
        free(block);
        return;
    }
    cg->blocks[cg->blockCount] = block;
    cg->blockCount++;
}

void addCGSuccessor(CGB* block, int successorIndex) {
    block->successors = (int*)realloc(block->successors, (block->successorCount + 1) * sizeof(int));
    if (!block->successors) {
        fprintf(stderr, "ERROR :: REALLOC FAILED\n");
        return;
    }
    block->successors[block->successorCount] = successorIndex;
    block->successorCount++;
}


void cgWalker(CG* cg, AST* node, int* lastBlockIndex) {
    for (int i = 0; i < node->childCount; i++) {
        cgWalker(cg, getChild(node, i), lastBlockIndex);
    }
}

int cgWalkerLinkWithParent(CG* cg, AST* current, int* lastBlockIndex) {
    CGB* cgb = createCallGraphBlock(current);
    if (!cgb)
        return -1;

    addCallGraphBlock(cg, cgb);
    int currentBlockIndex = cg->blockCount - 1;

    if (*lastBlockIndex != -1) {
        addCGSuccessor(cg->blocks[*lastBlockIndex], currentBlockIndex);
    }

    *lastBlockIndex = currentBlockIndex;

    printf("CG :: WLP :: %s\n", current->token);

    return currentBlockIndex;
}

CG* generateCG(AST* head, FunctionList* declaredFunctions) {
    return NULL;
}
