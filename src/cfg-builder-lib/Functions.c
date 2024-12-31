#include "Functions.h"
#include "CFGBuilder.h"

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
    if(func->cfg)
      freeCFG(func->cfg);
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


FunctionList* findFunctions(AST* head, char* filename) {
  FunctionList* functionList = createFunctionList();
  if(!functionList)
    return NULL;
  findFunctionsRecursive(functionList,head, filename);
  return functionList;
}
