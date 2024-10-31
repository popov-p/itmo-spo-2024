#include "InputOptions.h"
#include "AST.h"
#include "CFGBuilder.h"

#include "libgen.h"


FunctionList* createFunctionList() {
    FunctionList* list = (FunctionList*)malloc(sizeof(FunctionList));
    if (list) {
        list->items = NULL;
        list->count = 0;
    }
    return list;
}

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
        CFG* cfg = generateCFG(node);
        Function* func = createFunction(funcName->token, signature, cfg, filename);
        addFunction(functions, func);
    }
    for(int i = 0; i < node->childCount; ++i) {
        findFunctionsRecursive(functions, getChild(node, i), filename);
    }
}

Function* createFunction(const char* name, AST* signature, CFG* cfg, const char* sourceFile) {
    Function* func = (Function*)malloc(sizeof(Function));
    if (!func) return NULL;

    func->name = (char*)malloc(strlen(name) + 1);
    if (!func->name) {
        free(func);
        return NULL;
    }
    strncpy(func->name, name, strlen(name) + 1);

    func->signature = signature;
    func->cfg = cfg;

    func->sourceFile = (char*)malloc(strlen(sourceFile) + 1);
    if (!func->sourceFile) {
        free(func->name);
        free(func);
        return NULL;
    }
    strncpy(func->sourceFile, sourceFile, strlen(sourceFile) + 1);

    return func;
}

void addFunction(FunctionList* list, Function* func) {
    list->items = (Function**)realloc(list->items, (list->count + 1) * sizeof(Function*));
    if (list->items) {
        list->items[list->count] = func;
        list->count++;
    }
}

void freeFunction(Function* func) {
    if (func) {
        if (func->name)
            free(func->name);
        if (func->sourceFile)
            free(func->sourceFile);
        free(func);
    }
}

void processInput(int argc, char** argv) {
    const char* outputDir = argv[1];
    for (int i = 2; i < argc; ++i) { //for each file

        char *inputFilename = basename(argv[i]);
        char filenameNoExt[128];
        strncpy(filenameNoExt, inputFilename, sizeof(filenameNoExt) - 1);
        filenameNoExt[sizeof(filenameNoExt) - 1] = '\0';

        char outputSubDir[128];
        char *dot = strrchr(filenameNoExt, '.');
        if (dot) {
            *dot = '\0';
        }
        snprintf(outputSubDir, sizeof(outputSubDir), "%s/%s", outputDir, filenameNoExt);
        mkdir(outputSubDir, 0777);
        char *inputText = readFileToString(argv[i]);
        pParseResult parseResult = parse(inputText);
        AST* head = buildFromParseResult(parseResult);
        FunctionList* functionList = findFunctions(head, argv[i]);
        if(!functionList->count) {
            fprintf(stderr, "PI :: WARNING :: NO FUNCTIONS DETECTED");
            free(functionList);
            return;
        }
        for(int j = 0; j < functionList->count; j++) {
            char cfgDotFilename[64];
            snprintf(cfgDotFilename, sizeof(cfgDotFilename), "%s/%s-cfg.dot", outputSubDir, functionList->items[j]->name);
            FILE *cfgFile = fopen(cfgDotFilename, "w");
            if (!cfgFile)
                fprintf(stderr, "PI :: ERROR :: FILE NOT OPENED");
            outputCFG(functionList->items[j]->cfg, cfgFile);
            fclose(cfgFile);

            char cfgPngFilename[64];
            snprintf(cfgPngFilename, sizeof(cfgPngFilename), "%s/%s-cfg.png", outputSubDir, functionList->items[j]->name);

            char command[128];
            snprintf(command, sizeof(command), "dot -Tpng %s -o %s", cfgDotFilename, cfgPngFilename);
            int result = system(command);
            if (result)
                fprintf(stderr, "PI :: ERROR :: PNG FILE NOT GENERATED\n");
        }
        free(inputText);
        free(functionList);
    }
}

