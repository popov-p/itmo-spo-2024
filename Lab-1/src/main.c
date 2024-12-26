#include <stdio.h>
#include <stdlib.h>

#include "Treebuilder.h"

int main(int argc, char *argv[]) {
    // if (argc != 3) {
    //     printf("usage: %s <input file> <output file>\n", argv[0]);
    //     return 1;
    // }
    char *inputFilePath = "../src/for2.txt";//argv[1];
    char *outputFilePath = "../src/tree.dot";//argv[2];
    if (remove(outputFilePath) == 0) {
        printf("ok. file deleted %s\n", outputFilePath);
    } else {
        printf("not ok. file does not exist or deletion failed: %s\n", outputFilePath);
    }

    const char* compileGrammar = "antlr3 /home/pavel-ub/devel/itmo-spo-2024/Lab-1/src/Sigma.g";
    int res = system(compileGrammar);
    if (res == -1) {
        printf("not ok, failed antlr compiler\n");
    }
    else {
        printf("ok\n");
    }

    char *inputText = readFileToString(inputFilePath);
    if (inputText == NULL) {
        printf("not ok, failed reading from file\n");
    }

    pParseResult parseResult = parse(inputText);

    generateDot(parseResult, outputFilePath);
    const char *generateTree = "dot -Tpng ../src/tree.dot -o ../src/output.png";

    res = system(generateTree);
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

