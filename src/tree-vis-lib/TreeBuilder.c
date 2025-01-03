#include "TreeBuilder.h"
#include "safe_mem.h"
#include "commands.h"
char* readFileToString(const char* filePath) {
  FILE *file = open_file(filePath, "r");

  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = (char *)safe_malloc(fileSize + 1);

  fread(buffer, 1, fileSize, file);
  buffer[fileSize] = '\0';

  close_file(file);
  return buffer;
}

ParseResult* parse(const char* text) {
  ParseResult* result = (ParseResult*)safe_malloc(sizeof(ParseResult));

  result->is = antlr3StringStreamNew((pANTLR3_UINT8)text,
                                     ANTLR3_ENC_8BIT, strlen(text),
                                     (pANTLR3_UINT8)"input string");
  result->l = V4LexerNew(result->is);
  result->ts = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(result->l));
  result->p = V4ParserNew(result->ts);
  result->sr = result->p->source(result->p);
  return result;
}

void generateDot(ParseResult* result, const char* path) {
  pANTLR3_BASE_TREE_ADAPTOR treeAdaptor = result->p->adaptor;
  pANTLR3_STRING dotString = treeAdaptor->makeDot(treeAdaptor, result->sr.tree);

  FILE *dotFile = open_file(path, "w");
  fprintf(dotFile, "%s", (char *)dotString->chars);
  close_file(dotFile);
}

int cleanup(ParseResult* pr) {
  if (pr->p)
    pr->p->free(pr->p);
  if (pr->ts)
    pr->ts->free(pr->ts);
  if (pr->l)
    pr->l->free(pr->l);
  if (pr->is)
    pr->is->close(pr->is);
  if (!pr)
    return 1;
  else
    free(pr);
  return 0;
}
