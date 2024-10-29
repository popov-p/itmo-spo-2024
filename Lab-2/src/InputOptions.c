#include "InputOptions.h"
#include <unistd.h>
#include <stdio.h>
#include "AST.h"
#include "CFGBuilder.h"

void deleteFileIfExists(const char* filename) {
    if (access(filename, F_OK) != -1) {
        if (remove(filename) == 0) {
            printf("Deleted previous file: %s\n", filename);
        } else {
            perror("Failed to delete previous file");
        }
    }
}


void processInput(int argc, char** argv) {
    const char* outputDir = argv[1];
    File** files = (File**)malloc((argc-2)*sizeof(File*));
    for (int i = 2; i < argc; ++i) {
        char *inputText = readFileToString(argv[i]);
        pParseResult parseResult = parse(inputText);
        AST* head = buildFromParseResult(parseResult);
        char cfgDotFilename[512];
        char cfgPngFilename[512];
        snprintf(cfgDotFilename, sizeof(cfgDotFilename), "%s/cfg.dot", outputDir);
        snprintf(cfgPngFilename, sizeof(cfgPngFilename), "%s/cfg.png", outputDir);

        deleteFileIfExists(cfgDotFilename);
        deleteFileIfExists(cfgPngFilename);

        FILE *cfg_file = fopen(cfgDotFilename, "w");
        if (!cfg_file) {
            printf("not ok. cfg file creation failed %s\n", cfgDotFilename);
            free(inputText);
            continue;
        }

        // Генерация и вывод CFG
        CFG* cfg = generateCFG(head);
        outputCFG(cfg, cfg_file);

        fclose(cfg_file); // Закрываем файл cfg.dot
        printf("CFG записан в %s\n", cfgDotFilename);

        char command[1024];
        snprintf(command, sizeof(command), "dot -Tpng %s -o %s", cfgDotFilename, cfgPngFilename);
        system(command);

        printf("CFG изображение создано в %s\n", cfgPngFilename);

        // Очистка
        free(inputText);
    }
    free(files);
}
