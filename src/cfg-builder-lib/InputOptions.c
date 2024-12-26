#include "InputOptions.h"
#include "AST.h"
#include "Functions.h"
#include "CFGBuilder.h"
#include "CG.h"
#include "commands.h"

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
        else
            perror("FFR :: DEFINITION OF FUNCTIONS WITH EQUAL NAMES IS PROHIBITED\n");
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
        char* filename = getBaseName(argv[i]);
        char* outputSubDir = createFilePath("%s/%s", outputDir, filename);
        mkdir(outputSubDir, 0777);

        char *inputText = readFileToString(argv[i]);
        ParseResult* parseResult = parse(inputText);
        AST* head = buildFromParseResult(parseResult);

        FunctionList* functionList = findFunctions(head, argv[i]);
        CG* cg = generateCG(functionList);

        if(!functionList->count) {
            perror("PI :: WARNING :: NO FUNCTIONS DETECTED\n");
            free(functionList);
            return;
        }

        char* cgDotFilename = createFilePath("%s/%s-cg.dot", outputSubDir, filename);

        FILE* cgFile = fopen(cgDotFilename, "w");
        if (!cgFile)
            perror("PI:: ERROR :: CG DOT CREATION FAILED\n");
        else {
            outputCG(cg, cgFile);
            fclose(cgFile);
        }

        free(cgDotFilename);

        for(int j = 0; j < functionList->count; j++) {
            char* cfgDotFilename = createFilePath("%s/%s-cfg.dot", outputSubDir, functionList->items[j]->name);
            FILE *cfgFile = fopen(cfgDotFilename, "w");
            if (!cfgFile)
                fprintf(stderr, "PI :: ERROR :: FILE NOT OPENED");
            else {
                outputCFG(functionList->items[j]->cfg, cfgFile);
                fclose(cfgFile);
            }
            char* cfgPngFilename = createFilePath("%s/%s-cfg.png", outputSubDir, functionList->items[j]->name);
            executeCommand("dot -Tpng %s -o %s", cfgDotFilename, cfgPngFilename);
            free(cfgPngFilename);
        }
        free(inputText);
        free(functionList);
        cleanup(parseResult);
        free(cg);
        freeAST(head);
    }
}

