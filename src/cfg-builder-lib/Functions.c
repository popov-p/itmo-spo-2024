#include "Functions.h"
#include "safe_mem.h"

FL* FL_Create() {
  FL* list = (FL*)safe_malloc(sizeof(FL));
  if (list) {
    list->functions = NULL;
    list->count = 0;
  }
  return list;
}

void FL_Free(FL* list) {
  if (list) {
    for (int i = 0; i < list->count; i++) {
      if (list->functions[i])
        F_Free(list->functions[i]);
    }
    free(list->functions);
    free(list);
  }
}

void FL_AddF(FL* list, F* func) {
  list->functions = (F**)safe_realloc(list->functions, (list->count + 1) * sizeof(F*));
  list->functions[list->count] = func;
  list->count++;
}

void F_Free(F* func) {
  if (func) {
    if (func->name)
      free(func->name);
    if (func->sourceFile)
      free(func->sourceFile);
    if(func->cfg)
      CFG_Free(func->cfg);
    free(func);
  }
}

F* F_Create(const char* name, AST* signature, CFG* cfg, ST* symbolTable, const char* sourceFile) {
  F* func = (F*)safe_malloc(sizeof(F));
  if (!func) return NULL;

  func->name = (char*)safe_malloc(strlen(name) + 1);
  if (!func->name) {
    free(func);
    return NULL;
  }
  strncpy(func->name, name, strlen(name) + 1);

  func->signature = signature;
  func->cfg = cfg;

  func->sourceFile = (char*)safe_malloc(strlen(sourceFile) + 1);
  if (!func->sourceFile) {
    free(func->name);
    free(func);
    return NULL;
  }
  strncpy(func->sourceFile, sourceFile, strlen(sourceFile) + 1);

  return func;
}

int FL_FExists(FL* functionList, char* funcName) {
  for (int i = 0; i < functionList->count; ++i) {
    if (strcmp(functionList->functions[i]->name, funcName) == 0) {
      return 1;
    }
  }
  return 0;
}

void FL_FindFInAST(FL* functionList, AST* node, char* filename) {
  if(!strcmp(node->token, "AST_FUNC_DEF")) {
    AST* signature = AST_GetChild(node, 0);
    AST* funcName = AST_GetChild(signature, 0);

    if (!FL_FExists(functionList, funcName->token)) {
      F* func = F_Create(funcName->token, signature,
                         CFG_Generate(node), NULL, filename);
      FL_AddF(functionList, func);

    }
    else
      perror("FFR :: DEFINITION OF FUNCTIONS WITH EQUAL NAMES IS PROHIBITED\n");
  }
  for(int i = 0; i < node->childCount; ++i)
    FL_FindFInAST(functionList, AST_GetChild(node, i), filename);
}

FL* FL_FindFsInAST(AST* head, char* filename) {
  FL* functionList = FL_Create();
  if(!functionList)
    return NULL;
  FL_FindFInAST(functionList, head, filename);
  return functionList;
}
