#ifndef TREEBUILDER_H
#define TREEBUILDER_H

#include "SigmaLexer.h"
#include "SigmaParser.h"

typedef struct ParseResult {
    pANTLR3_INPUT_STREAM is;
    pSigmaLexer l;
    pANTLR3_COMMON_TOKEN_STREAM ts;
    pSigmaParser p;
    SigmaParser_source_return sr;
} ParseResult;

typedef ParseResult* pParseResult;

char* readFileToString(const char* filePath);

pParseResult parse(const char* text);

void generateDot(pParseResult result, const char* path);

int cleanup(pParseResult pr);

#endif // TREEBUILDER_H
