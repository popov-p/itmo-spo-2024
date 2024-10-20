#include <stdlib.h>
#include <stdio.h>
#include <antlr3.h>

#include "CFGBuilder.h"
#include "AST.h"

int main(int argc, char *argv[]) {
    char *inputText = readFileToString("../test.txt");

    if (inputText == NULL) {
        printf("not ok. failed reading from file\n");
    }

    pParseResult parseResult = parse(inputText);
    AST* head = buildFromParseResult(parseResult);

    const char* tree_filename = "../src/tree.dot";
    FILE *tree_file = fopen(tree_filename, "w");
    if (tree_file == NULL) {
        perror("not ok, cannot open cfg file");
        return -1;
    }
    printAST(head, tree_file);
    fclose(tree_file);

    const char* cfg_filename = "../src/cfg.dot";
    FILE *cfg_file = fopen(cfg_filename, "w");
    if (cfg_file == NULL) {
        perror("not ok, cannot open cfg file");
        return -1;
    }

    CFG* cfg = generateCFG(head);
    outputCFG(cfg, cfg_file);
    fclose(cfg_file);

    return 0;
}

