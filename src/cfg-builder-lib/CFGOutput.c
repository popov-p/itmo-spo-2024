#include "CFGOutput.h"
#include "OTOutput.h"

void CFG_WriteBlock(int num, FILE *file, BB_t type) {
  if (type == standard)
    fprintf(file, "    node%d [label=\"BB%d\"];\n", num, num);
  if (type == merge)
    fprintf(file, "    node%d [label=\"MRG\"];\n", num);
  if (type == loop_exit)
    fprintf(file, "    node%d [label=\"LPXT\"];\n", num);
  if (type == repeat_exit)
    fprintf(file, "    node%d [label=\"RPXT\"];\n", num);
}

void CFG_WriteEdges(CFG* cfg, FILE *file) {
  for (int i = 0; i < cfg->blockCount; i++) {
    for(int j = 0; j < cfg->blocks[i]->successorCount; j++)
      fprintf(file, "    node%d -> node%d;\n", i, cfg->blocks[i]->successors[j]);
  }
}

void CFG_WriteInFile(CFG* cfg, FILE* file) {
  fprintf(file, "digraph G {\n");
  fprintf(file, "    rankdir=TB;\n");
  fprintf(file, "    start [label=\"%s\"];\n", "Начало");
  fprintf(file, "    end [label=\"%s\"];\n", "Конец");

  if(!cfg->blockCount) {
    fprintf(file, "    start -> end;\n");
    return;
  }

  for (int i = 0; i < cfg->blockCount; i++) {
    BB* bb = cfg->blocks[i];
    CFG_WriteBlock(i, file, bb->bt);
  }

  CFG_WriteEdges(cfg, file);
  fprintf(file, "    start -> node%d;\n", 0);
  for (int i = 0; i < cfg->blockCount; i++) {
    BB* bb = cfg->blocks[i];
    if (!bb->successorCount)
      fprintf(file, "    node%d -> end;\n", i);
  }
  for (int i = 0; i < cfg->blockCount; i++)
    CFG_WriteOT(cfg, i, file);
  fprintf(file, "}\n");
}

void CFG_WriteOT(CFG* cfg, int basicBlockIndex, FILE* file) {
  BB* bb = cfg->blocks[basicBlockIndex];
  if (bb->node) {
    fprintf(file, "subgraph cluster_%d {\n", basicBlockIndex);
    fprintf(file, "    label=\"%s%d\";\n", "BB", basicBlockIndex);

    OT_PrintTree(bb->opTree, 0);
    OT_WriteNodes(bb->opTree, basicBlockIndex, file);
    OT_WriteEdges(bb->opTree, basicBlockIndex, file);
    fprintf(file, "}\n");
  }
}
