#include "AG.h"
int main(int argc, char** argv) {
  AS* set = AS_init();

  AS_addAddr(set, 0x000A);
  AS_addAddr(set, 0xFFFF);
  AS_addAddr(set, 0x1234);

  AS_print(set);

  if (AS_containsAddr(set, 0x000A)) {
    printf("0x000A is in the set\n");
  }

  AS_removeAddr(set, 0x000A);
  AS_print(set);

  AG *gen = AG_init(0x0000, 0xFFFF);
  if (!gen) {
    fprintf(stderr, "Failed to initialize AddressGenerator\n");
    return 1;
  }

  unsigned short addr;
  while (AG_next(gen, &addr)) {
    printf("Sequential address: 0x%04X\n", addr);
  }

  AG_destroy(gen); // Освобождаем память
  AS_free(set);
  return 0;

  // return 0;
}
