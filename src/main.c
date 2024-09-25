#include <stdio.h>
#include <antlr3.h>
#include "Var4Lexer.h"
#include "Var4Parser.h"

#include <stdlib.h>

void generateDot(pANTLR3_STRING dotString, char* path) {
    FILE *dotFile = fopen(path, "w");
    if (dotFile != NULL) {
        fprintf(dotFile, "%s", (char *)dotString->chars);
        fclose(dotFile);
    } else {
        printf("Ошибка при открытии файла для записи.\n");
    }
}

int main(int argc, char *argv[]) {

    const char* compile_grammar = "java -jar ../src/antlr-3.4-complete.jar ../src/Var4.g";
    int res = system(compile_grammar);
    if (res == -1) {
        printf("not ok\n");
    }
    else {
        printf("ok\n");
    }

    pANTLR3_INPUT_STREAM input = antlr3FileStreamNew((pANTLR3_UINT8)"../src/test.txt", ANTLR3_ENC_8BIT);

    pVar4Lexer lex = Var4LexerNew(input);

    pANTLR3_COMMON_TOKEN_STREAM tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lex));
    pVar4Parser parser = Var4ParserNew(tokens);

    Var4Parser_source_return parseResult = parser->source(parser);
    pANTLR3_BASE_TREE_ADAPTOR treeAdaptor = parser->adaptor;
    pANTLR3_STRING dotString = treeAdaptor->makeDot(treeAdaptor, parseResult.tree);

    generateDot(dotString, "../src/tree.dot");
    const char *generate_tree = "dot -Tpng ../src/tree.dot -o ../src/output.png";

    res = system(generate_tree);
    if (res == -1) {
        printf("not ok\n");
    }
    else {
        printf("ok\n");
    }

    parser->free(parser);
    tokens->free(tokens);
    lex->free(lex);
    input->close(input);

    return 0;
}

