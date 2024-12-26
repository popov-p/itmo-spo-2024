#include "TreeBuilder.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("usage: %s <input file> <output dir>\n", argv[0]);
        return 1;
    }
    char *inputFilePath = argv[1];
    char *outputDir = argv[2];

    char *fileName = strrchr(inputFilePath, '/');
    fileName = (fileName) ? fileName + 1 : inputFilePath;

    char baseName[256];
    snprintf(baseName, sizeof(baseName), "%s", fileName);
    char *dot = strrchr(baseName, '.');
    if (dot)
        *dot = '\0';


    size_t dotLen = snprintf(NULL, 0, "%s/%s.dot", outputDir, baseName) + 1;
    char* dotFilePath = (char*)malloc(dotLen);
    if (!dotFilePath)
        fprintf(stderr, "not onemory allocation failed\n");
    snprintf(dotFilePath, dotLen, "%s/%s.dot", outputDir, baseName);

    size_t pngLen = snprintf(NULL, 0, "%s/%s.png", outputDir, baseName) + 1;
    char* pngFilePath = (char*)malloc(pngLen);
    if (!pngFilePath)
        fprintf(stderr, "Memory allocation failed\n");
    snprintf(pngFilePath, pngLen, "%s/%s.png", outputDir, baseName);

    char *inputText = readFileToString(inputFilePath);
    if (!inputText)
        printf("not ok, failed reading from file\n");

    ParseResult* parseResult = parse(inputText);

    generateDot(parseResult, dotFilePath);

    char genPngCommand[256];
    snprintf(genPngCommand, sizeof(genPngCommand), "dot -Tpng %s -o %s", dotFilePath, pngFilePath);
    int commandResult = system(genPngCommand);
    if (commandResult != 0) {
        printf("Failed to generate PNG from dot file.\n");
        cleanup(parseResult);
        return 1;
    }

    char openCommand[256];
    snprintf(openCommand, sizeof(openCommand), "xdg-open %s", pngFilePath);
    system(openCommand);
    free(inputText);
    cleanup(parseResult);
    return 0;
}
