#ifndef TREEBUILDER_H
#define TREEBUILDER_H

#include "Var4Lexer.h"
#include "Var4Parser.h"

typedef struct ParseResult {
    pANTLR3_INPUT_STREAM is;
    pVar4Lexer l;
    pANTLR3_COMMON_TOKEN_STREAM ts;
    pVar4Parser p;
    Var4Parser_source_return sr;
} ParseResult;

typedef ParseResult* pParseResult;

char* readFileToString(const char* filePath);

pParseResult parse(const char* text);

void generateDot(pParseResult result, const char* path);

int cleanup(ParseResult* pr);

#endif // TREEBUILDER_H
