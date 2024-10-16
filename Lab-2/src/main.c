#include <stdio.h>
#include <stdlib.h>

#include "CFGBuilder.h"

int main(int argc, char *argv[]) {
    char *inputText = readFileToString("../test.txt");

    if (inputText == NULL) {
        printf("not ok. failed reading from file\n");
    }

    pParseResult parseResult = parse(inputText);
    walk_parse_tree(parseResult);
    if(!cleanup(parseResult)) {
        printf("not ok. cleanup failed");
    }
    return 0;
}

