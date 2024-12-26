#include "TreeBuilder.h"
#include "commands.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("usage: %s <input file> <output dir>\n", argv[0]);
        return 1;
    }
    char *inputFilePath = argv[1];
    char *outputDir = argv[2];

    char* baseName = getBaseName(inputFilePath);

    char* dotFilePath = createFilePath("%s/%s.dot", outputDir, baseName);
    char* pngFilePath = createFilePath("%s/%s.png", outputDir, baseName);

    char *inputText = readFileToString(inputFilePath);
    if (!inputText)
        printf("not ok, failed reading from file\n");

    ParseResult* parseResult = parse(inputText);

    generateDot(parseResult, dotFilePath);

    executeCommand("Failed to generate PNG from dot file.",
                   "dot -Tpng %s -o %s",
                    dotFilePath, pngFilePath);

    executeCommand("Failed to open PNG file with xdg-open.",
                   "xdg-open %s",
                   pngFilePath);

    free(pngFilePath);
    free(dotFilePath);
    free(inputText);
    free(baseName);
    cleanup(parseResult);
    return 0;
}
