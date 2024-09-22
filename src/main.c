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

int main() {
    const char *inputString = "def test ( ) begin x = false ; end";

    pANTLR3_INPUT_STREAM input = antlr3StringStreamNew((pANTLR3_UINT8)inputString, ANTLR3_ENC_8BIT, strlen(inputString), (pANTLR3_UINT8)"input");

    pVar4Lexer lexer = Var4LexerNew(input);
    pANTLR3_COMMON_TOKEN_STREAM tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));

    pVar4Parser parser = Var4ParserNew(tokenStream);

    Var4Parser_source_return res = parser->source(parser);

    pANTLR3_BASE_TREE tree = res.tree;

    printAST(tree, 0);

    parser->free(parser);
    tokenStream->free(tokenStream);
    lexer->free(lexer);
    input->free(input);

    return 0;
}

