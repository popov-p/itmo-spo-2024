#include "ASMGen.h"

void ASM_GenerateListing(F* function, FILE* listing) {
  fprintf(listing, "[section progmem]\n");
  fprintf(listing, "%s:\n", function->name);
  for (int i = 0; i < function->cfg->blockCount; i++) {
    BB* block = function->cfg->blocks[i];
    if (block && block->opTree) {
      ASM_Walker(block->opTree, listing);
    }
  }
  fprintf(listing, "\thalt\n");
}

void ASM_Walker(OT* node, FILE* listing) {
  if (!node)
    return;
  printf("----> visiting: %d\n", node->dataType);
  for(int i = 0; i < node->childCount; i++) {
    OT* child = OT_GetChild(node, i);
    ASM_Walker(child, listing);
  }
  if(IS_OPERATION(node, __WRITE)) {
    printf("----> found __WRITE\n");
    fprintf(listing, "\tstloc 0x%04X\n", 0x001);
  }
  if(IS_OPERATION(node, __PLUS)) {
    printf("----> found __PLUS\n");
    fprintf(listing, "\tadd\n");
  }
  if(IS_CONSTANT(node)) {
    printf("----> found CONSTANT\n");
    fprintf(listing, "\tldc %d\n", atoi(node->data.constant.value));
  }
  // if(IS_VARIABLE(node)) {
  //   printf("----> found VARIABLE\n");
  //   fprintf(listing, "\tldloc %x\n", 0x1234);
  // }
}
