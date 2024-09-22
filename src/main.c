#include <stdio.h>
#include <antlr3.h>
#include "Var4PrevLexer.h"
#include "Var4PrevParser.h"

void printASTgraphviz(pANTLR3_BASE_TREE tree, FILE *file, int *nodeCounter) {
    int currentNode = (*nodeCounter)++;
    fprintf(file, "  node%d [label=\"%s\"];\n", currentNode, (char *)tree->toString(tree)->chars);

    for (unsigned i = 0; i < tree->getChildCount(tree); ++i) {
        pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild(tree, i);
        int childNode = (*nodeCounter);

        printASTgraphviz(child, file, nodeCounter);

        fprintf(file, "  node%d -> node%d;\n", currentNode, childNode - 1);
    }
}



void generateDotFile(pANTLR3_BASE_TREE ast) {
    FILE *file = fopen("../src/tree.dot", "w");
    if (file == NULL) {
        perror("Cannot open file to write");
        return;
    }

    fprintf(file, "digraph AST {\n");
    fprintf(file, "  node [shape=ellipse];\n");

    int nodeCounter = 0;
    printASTgraphviz(ast, file, &nodeCounter);

    fprintf(file, "}\n");
    fclose(file);
}

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

    pVar4PrevLexer lex = Var4PrevLexerNew(input);

    pANTLR3_COMMON_TOKEN_STREAM tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lex));
    pVar4PrevParser parser = Var4PrevParserNew(tokens);

    Var4PrevParser_source_return parseResult = parser->source(parser);
    printAST(parseResult.tree, 0);
    generateDotFile(parseResult.tree);
    parser->free(parser);
    tokens->free(tokens);
    lex->free(lex);
    input->close(input);

    return 0;
}

