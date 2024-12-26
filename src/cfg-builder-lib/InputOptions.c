#include "InputOptions.h"
#include "AST.h"
#include "Functions.h"
#include "CFGBuilder.h"
#include "CG.h"

#include "libgen.h"

FunctionList* findFunctions(AST* head, char* filename) {
    FunctionList* functionList = createFunctionList();
    if(!functionList)
        return NULL;
    findFunctionsRecursive(functionList,head, filename);
    return functionList;
}

void findFunctionsRecursive(FunctionList* functions, AST* node, char* filename) {
    if(!strcmp(node->token, "FUNC_DEF")) {
        AST* signature = getChild(node, 0);
        AST* funcName = getChild(signature, 0);

        if (!functionExists(functions, funcName->token)) {
            CFG* cfg = generateCFG(node);

            Function* func = createFunction(funcName->token, signature, cfg, filename);
            addFunction(functions, func);
        }
        else{
            fprintf(stderr, "FFR :: DEFINITION OF FUNCTIONS WITH EQUAL NAMES IS PROHIBITED\n");
        }
    }
    for(int i = 0; i < node->childCount; ++i) {
        findFunctionsRecursive(functions, getChild(node, i), filename);
    }
}

void processInput(int argc, char** argv) {
    const char* outputDir = argv[1];

    struct stat st = {0};
    if (stat(outputDir, &st) == -1) {
        if (mkdir(outputDir, 0777) == -1) {
            perror("PI :: ERROR :: FAILED TO CREATE OUTPUT DIRECTORY");
            return;
        }
    }

    for (int i = 2; i < argc; ++i) { //for each file
        char *inputFilename = basename(argv[i]);
        char filenameNoExt[256];
        strncpy(filenameNoExt, inputFilename, sizeof(filenameNoExt) - 1);
        filenameNoExt[sizeof(filenameNoExt) - 1] = '\0';

        char outputSubDir[256];
        char *dot = strrchr(filenameNoExt, '.');
        if (dot) {
            *dot = '\0';
        }
        snprintf(outputSubDir, sizeof(outputSubDir), "%s/%s", outputDir, filenameNoExt);
        mkdir(outputSubDir, 0777);


        char *inputText = readFileToString(argv[i]);
        ParseResult* parseResult = parse(inputText);
        AST* head = buildFromParseResult(parseResult);

        char treeDotFilename[256];
        snprintf(treeDotFilename, sizeof(treeDotFilename), "%s/%s.dot", outputSubDir, filenameNoExt);
        FILE *treeFile = fopen(treeDotFilename, "w");
        if (!treeFile) {
            fprintf(stderr, "PI :: ERROR :: FILE NOT OPENED\n");
            free(inputText);
            return;
        }
        printAST(head, treeFile);
        fclose(treeFile);

        char treePngFilename[256];
        snprintf(treePngFilename, sizeof(treePngFilename), "%s/%s.png", outputSubDir, filenameNoExt);
        char command[256];
        snprintf(command, sizeof(command), "dot -Tpng %s -o %s", treeDotFilename, treePngFilename);
        int result = system(command);
        if (result) {
            fprintf(stderr, "PI :: ERROR :: PNG GENERATION FAILED\n");
        }

        FunctionList* functionList = findFunctions(head, argv[i]);
        CG* cg = generateCG(functionList);

        if(!functionList->count) {
            fprintf(stderr, "PI :: WARNING :: NO FUNCTIONS DETECTED\n");
            free(functionList);
            return;
        }

        char cgDotFilename[256];
        snprintf(cgDotFilename, sizeof(cgDotFilename), "%s/%s-cg.dot", outputSubDir, filenameNoExt);

        FILE* cgFile = fopen(cgDotFilename, "w");
        if (!cgFile) {
            perror("PI:: ERROR :: CG DOT CREATION FAILED\n");
            return;
        }
        outputCG(cg, cgFile);
        fclose(cgFile);

        char cgPngFilename[256];
        snprintf(cgPngFilename, sizeof(cgPngFilename), "%s/%s-cg.png", outputSubDir, filenameNoExt);

        snprintf(command, sizeof(command), "dot -Tpng %s -o %s", cgDotFilename, cgPngFilename);
        result = system(command);
        if (result) {
            fprintf(stderr, "PI :: ERROR :: CALL GRAPH PNG GENERATION FAILED \n");
        }


        for(int j = 0; j < functionList->count; j++) {
            char cfgDotFilename[256];
            snprintf(cfgDotFilename, sizeof(cfgDotFilename), "%s/%s-cfg.dot", outputSubDir, functionList->items[j]->name);
            FILE *cfgFile = fopen(cfgDotFilename, "w");
            if (!cfgFile)
                fprintf(stderr, "PI :: ERROR :: FILE NOT OPENED");
            else {
                outputCFG(functionList->items[j]->cfg, cfgFile);
                fclose(cfgFile);
            }
            char cfgPngFilename[256];
            snprintf(cfgPngFilename, sizeof(cfgPngFilename), "%s/%s-cfg.png", outputSubDir, functionList->items[j]->name);

            char command[256];
            snprintf(command, sizeof(command), "dot -Tpng %s -o %s", cfgDotFilename, cfgPngFilename);
            int result = system(command);
            if (result)
                fprintf(stderr, "PI :: ERROR :: PNG FILE NOT GENERATED\n");
        }
        free(inputText);
        free(functionList);
        cleanup(parseResult);
        free(cg);
        freeAST(head);
    }
}

