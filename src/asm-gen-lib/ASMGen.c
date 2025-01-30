#include "ASMGen.h"

void ASM_GenerateListing(AS* set, F* function, FILE* listing) {
  ASMFW fw;
  fw.function = function;
  fw.set = set;
  fw.function->symbolTable = function->cfg->symbolTable;
  fprintf(listing, "[section progmem]\n");
  fprintf(listing, "%s:\n", fw.function->name);
  for (int i = 0; i < fw.function->cfg->blockCount; i++) {
    BB* block = fw.function->cfg->blocks[i];
    if (block && block->opTree)
      ASM_Walker(&fw, block->opTree, listing);
  }
  fprintf(listing, "\thalt\n");
}

void ASM_Walker(ASMFW* fw, OT* node, FILE* listing) {
  if (!node)
    return;
  printf("----> visiting: %d\n", node->dataType);
  for(int i = 0; i < node->childCount; i++) {
    OT* child = OT_GetChild(node, i);
    ASM_Walker(fw, child, listing);
  }
  if(IS_OPERATION(node, __WRITE)) {
    OT* ot_var = OT_GetChild(node, 0); // left child with variable
    STE* st_var = ST_Search(fw->function->symbolTable, ot_var->data.variable.name, ST_VAR);

    printf("----> found __WRITE\n");
    AG_nextUnique(fw->set, &st_var->addr);

    fprintf(listing, "\tstloc 0x%04X\n", st_var->addr);
  }
  if(IS_OPERATION(node, __PLUS)) {
    printf("----> found __PLUS\n");
    fprintf(listing, "\tadd\n");
  }
  if(IS_CONSTANT(node)) {
    printf("----> found CONSTANT\n");
    fprintf(listing, "\tpush %d\n", atoi(node->data.constant.value));
  }
  // if(IS_VARIABLE(node)) {
  //   printf("----> found VARIABLE\n");
  //   STE* var = ST_Search(fw->function->symbolTable, node->data.variable.name, ST_VAR);
  //   AG_nextUnique(fw->set, &var->addr);
  //   fprintf(listing, "\tldloc %x\n", var->addr);
  // }
}
