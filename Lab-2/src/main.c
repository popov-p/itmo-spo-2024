#include <stdlib.h>
#include <stdio.h>
#include <antlr3.h>

#include "CFGBuilder.h"
#include "HashTree.h"

int main(int argc, char *argv[]) {
    char *inputText = readFileToString("../test.txt");

    if (inputText == NULL) {
        printf("not ok. failed reading from file\n");
    }

    pParseResult parseResult = parse(inputText);
    traverseTree(parseResult->p->adaptor, parseResult->sr.tree);

    const char* cfg_filename = "../src/cfg.dot";
    FILE *cfg_file = fopen(cfg_filename, "w");
    if (cfg_file == NULL) {
        perror("not ok, cannot open cfg file");
        return -1;
    }
    CFG* cfg = generateCFG(parseResult);
    outputCFG(parseResult, cfg, cfg_file);
    fclose(cfg_file);

    return 0;
}

