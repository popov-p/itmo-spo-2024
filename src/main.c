#include <stdio.h>
#include <stdlib.h>

#include "Treebuilder.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    char *inputFilePath = argv[1];
    char *outputFilePath = argv[2];
    const char* compile_grammar = "java -jar ../src/antlr-3.4-complete.jar ../src/Var4.g";
    int res = system(compile_grammar);
    if (res == -1) {
        printf("not ok, failed antlr compiler\n");
    }
    else {
        printf("ok\n");
    }

    char *inputText = readFileToString(inputFilePath);
    if (inputText == NULL) {
        printf("not ok. failed reading from file\n");
    }

    pParseResult parseResult = parse(inputText);

    generateDot(parseResult, outputFilePath);
    const char *generate_tree = "dot -Tpng ../src/tree.dot -o ../src/output.png";

    res = system(generate_tree);
    if (res == -1) {
        printf("not ok, failed tree generation\n");
    }
    else {
        printf("ok\n");
    }
    if (!cleanup(parseResult)) {
        printf("ok\n");
    }
    else {
        printf("not ok. cleanup failed\n");
    }
    return 0;
}

