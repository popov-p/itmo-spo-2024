#include "Functions.h"


FunctionList* createFunctionList() {
    FunctionList* list = (FunctionList*)malloc(sizeof(FunctionList));
    if (list) {
        list->items = NULL;
        list->count = 0;
    }
    return list;
}

void freeFunctionList(FunctionList* list) {
    if (list) {
        for (int i = 0; i < list->count; i++) {
            if (list->items[i])
                freeFunction(list->items[i]);
        }
        free(list->items);
        free(list);
    }
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

int functionExists(FunctionList* functions, char* funcName) {
    for (int i = 0; i < functions->count; ++i) {
        if (strcmp(functions->items[i]->name, funcName) == 0) {
            return 1;
        }
    }
    return 0;
}


