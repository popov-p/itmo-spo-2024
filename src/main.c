#include <stdio.h>
#include <antlr3.h>
#include "TLexer.h"
#include "TParser.h"

int main(int argc, char** argv) {
  if (argc != 2) {
      fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
      return 1;
    }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
      perror("fopen");
      return 1;
    }
  //TLexer* lexer = TLexerNew(file);
}
