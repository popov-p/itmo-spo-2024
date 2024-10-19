#include <stdlib.h>
#include <stdio.h>
#include <antlr3.h>

#include "CFGBuilder.h"

int main(int argc, char *argv[]) {
    char *inputText = readFileToString("../test.txt");

    if (inputText == NULL) {
        printf("not ok. failed reading from file\n");
    }

    pParseResult parseResult = parse(inputText);
    //walk_parse_tree(parseResult);

    //const char* tree_filename = "../src/tree.dot";
    //FILE *tree_file = fopen(tree_filename, "w");
    //if (tree_file == NULL) {
    //    perror("not ok, cannot open tree file");
    //    return -1;
    //}
    //generate_parse_tree(parseResult->sr.tree, tree_file);
    //fclose(tree_file);

    const char* cfg_filename = "../src/cfg.dot";
    FILE *cfg_file = fopen(cfg_filename, "w");
    if (cfg_file == NULL) {
        perror("not ok, cannot open cfg file");
        return -1;
    }
    CFG* cfg = generateCFG(parseResult);
    outputCFG(cfg, cfg_file);
    //generate_cfg(parseResult->sr.tree, cfg_file);
    //generate_cfg_from_CFG(parseResult->sr.tree, cfg_file);
    fclose(cfg_file);

    return 0;
}

