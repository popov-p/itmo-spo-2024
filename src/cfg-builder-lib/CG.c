#include "CG.h"
#include "safe_mem.h"

CG* initEmptyCG() {
  CG* cg = (CG*)safe_malloc(sizeof(CG));

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
  CGB* block = (CGB*)safe_malloc(sizeof(CGB));

  block->node = node;
  block->successors = NULL;
  block->successorCount = 0;
  return block;
}
void addCallGraphBlock(CG* cg, CGB* block) {
  cg->blocks = (CGB**)safe_realloc(cg->blocks,(cg->blockCount + 1) * sizeof(CGB*));
  cg->blocks[cg->blockCount] = block;
  cg->blockCount++;
}

void addCGSuccessor(CGB* block, int successorIndex) {
  block->successors = (int*)safe_realloc(block->successors, (block->successorCount + 1) * sizeof(int));
  block->successors[block->successorCount] = successorIndex;
  block->successorCount++;
}

CG* generateCG(FunctionList* declaredFunctions) {
  CG* cg = initEmptyCG();
  for(int i = 0; i < declaredFunctions->count; i++) {
    CGB* currentFunction = createCallGraphBlock(declaredFunctions->items[i]->signature);
    addCallGraphBlock(cg, currentFunction);
    for(int j = 0; j < declaredFunctions->items[i]->cfg->blockCount; j++) {
      if((declaredFunctions->items[i]->cfg->blocks[j]->node) && !strcmp(declaredFunctions->items[i]->cfg->blocks[j]->node->token, "CALL")) {
        int currentCallIndex = findIndexByName(declaredFunctions,
                                               getChild(declaredFunctions->items[i]->cfg->blocks[j]->node, 0));
        if(currentCallIndex != -1) {
          addCGSuccessor(currentFunction, currentCallIndex);
        }
        else {
          fprintf(stderr, "GEN CG :: CALL OF UNDECLARED FUNCTION\n");
        }
      }
    }
  }
  return cg;
}


int findIndexByName(FunctionList* declaredFunctions, AST* name) {
  for(int i = 0; i < declaredFunctions->count; i++) {
    if (!strcmp(declaredFunctions->items[i]->name, name->token))
      return i;
  }
  return -1;
}

void outputCG(CG* cg, FILE* file) {
  fprintf(file, "digraph CallGraph {\n");
  outputCgNodes(cg, file);
  outputCgEdges(cg, file);
  fprintf(file, "}\n");
}

void outputCgNodes(CG* cg, FILE* file) {
  for (int i = 0; i < cg->blockCount; ++i) {
    fprintf(file, "    node%u [label=\"%s\"];\n", cg->blocks[i]->node->id,
            getChild(cg->blocks[i]->node, 0)->token);
  }
}

void outputCgEdges(CG* cg, FILE* file) {
  for (int i = 0; i < cg->blockCount; ++i) {
    CGB* block = cg->blocks[i];

    for (int j = 0; j < block->successorCount; ++j) {
      int successorIndex = block->successors[j];
      fprintf(file, "    node%u -> node%u;\n", block->node->id, cg->blocks[successorIndex]->node->id);
    }
  }
}

