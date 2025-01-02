#ifndef TREEBUILDER_H
#define TREEBUILDER_H

#include "V4Lexer.h"
#include "V4Parser.h"

typedef struct ParseResult {
    pANTLR3_INPUT_STREAM is;
    pV4Lexer l;
    pANTLR3_COMMON_TOKEN_STREAM ts;
    pV4Parser p;
    V4Parser_source_return sr;
} ParseResult;

char* readFileToString(const char* filePath);
ParseResult* parse(const char* text);
void generateDot(ParseResult* result, const char* path);
int cleanup(ParseResult* pr);

#endif // TREEBUILDER_H
