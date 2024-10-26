#include <stdlib.h>
#include <stdio.h>
#include <antlr3.h>

#include "CFGBuilder.h"
#include "AST.h"

void deleteFileIfExists(const char* filename) {
    if (access(filename, F_OK) != -1) {
        if (remove(filename) == 0) {
            printf("Deleted previous file: %s\n", filename);
        } else {
            perror("Failed to delete previous file");
        }
    }
}

int main(int argc, char *argv[]) {
    char *inputText = readFileToString("../src/test.txt");

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

    const char* cfgDotFilename = "../src/cfg.dot";
    const char* cfgPngFilename = "../src/cfg.png";
    deleteFileIfExists(cfgDotFilename);
    deleteFileIfExists(cfgPngFilename);


    const char* cfg_filename = "../src/cfg.dot";
    FILE *cfg_file = fopen(cfg_filename, "w");
    if (cfg_file == NULL) {
        perror("not ok, cannot open cfg file");
        return -1;
    }

    CFG* cfg = generateCFG(head);
    outputCFG(cfg, cfg_file);
    fclose(cfg_file);


    char dot_command[256];
    snprintf(dot_command, sizeof(dot_command), "dot -Tpng %s -o %s", cfgDotFilename, cfgPngFilename);
    int result = system(dot_command);

    if (result == -1) {
        perror("not ok, failed to generate cfg.png");
        return -1;
    } else {
        printf("cfg.png generated successfully.\n");
    }

    return 0;
}

