#include <stdio.h>
#include <antlr3.h>
#include "Var4Lexer.h"
#include "Var4Parser.h"

void printAST(pANTLR3_BASE_TREE tree, int depth) {
    if (tree == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    pANTLR3_STRING text = tree->toString(tree);
    printf("%s\n", (char*) text->chars);

    for (int i = 0; i < tree->getChildCount(tree); i++) {
        printAST((pANTLR3_BASE_TREE) tree->getChild(tree, i), depth + 1);
    }
}

int main(int argc, char *argv[]) {
    pANTLR3_INPUT_STREAM input = antlr3FileStreamNew((pANTLR3_UINT8)"../src/test.txt", ANTLR3_ENC_8BIT);
    if (input == NULL) {
        fprintf(stderr, "Failed to open input file: %s\n", argv[1]);
        return 1;
    }

    pVar4Lexer lex = Var4LexerNew(input);
    if (lex == NULL) {
        fprintf(stderr, "Failed to create lexer\n");
        input->close(input);
        return 1;
    }

    pANTLR3_COMMON_TOKEN_STREAM tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lex));



    pVar4Parser parser = Var4ParserNew(tokens);

    Var4Parser_source_return parseResult = parser->source(parser);
    printAST(parseResult.tree, 0);

    parser->free(parser);
    tokens->free(tokens);
    lex->free(lex);
    input->close(input);

    return 0;
}

