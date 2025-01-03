#include "safe_mem.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ST.h"

// #define RANDOM_KEY() ({ \
//     unsigned int key = arc4random(); \
//     char *key_str = (char *)malloc(11 * sizeof(char)); \
//     snprintf(key_str, 11, "%u", key); \
//     key_str; \
// })

ST *ST_Create(int capacity) {
  ST *table = (ST *)safe_malloc(sizeof(ST));
  table->capacity = capacity;
  table->size = 0;
  table->entries = (STE *)safe_malloc(capacity * sizeof(STE));
  return table;
}

void ST_Free(ST *table) {
  for (int i = 0; i < table->size; i++) {
    free(table->entries[i].key);
    switch (table->entries[i].type) {
      case CONSTANT:
        free(table->entries[i].value.constant.type);
        break;
      case VAR:
        free(table->entries[i].value.variable.name);
        free(table->entries[i].value.variable.type);
        break;
      case FUNC:
        free(table->entries[i].value.function.name);
        free(table->entries[i].value.function.returnType);
        break;
    }
  }
  free(table->entries);
  free(table);
}

void ST_Resize(ST *table) {
  int new_capacity = table->capacity * 2;
  STE* new_entries = (STE *)safe_malloc(new_capacity * sizeof(STE));

  for (int i = 0; i < table->size; i++) {
    new_entries[i] = table->entries[i];
  }

  free(table->entries);
  table->entries = new_entries;
  table->capacity = new_capacity;
}

STE* ST_Search(ST *table, const char *key) {
  for (int i = 0; i < table->size; i++) {
    if (strcmp(table->entries[i].key, key) == 0) {
      return &table->entries[i];
    }
  }
  return NULL;
}

void ST_InsertConstant(ST *table, const char *key, const char *type) {
  STE *entry = ST_Search(table, key);

  if (entry) {
    free(entry->value.constant.type);
    entry->value.constant.type = strdup(type);
    return;
  }

  if (table->size == table->capacity) {
    ST_Resize(table);
  }

  entry = &table->entries[table->size++];
  entry->key = strdup(key);
  entry->type = CONSTANT;
  entry->value.constant.type = strdup(type);
}

void ST_InsertVariable(ST *table, const char *key, const char *name, const char *type) {
  STE *entry = ST_Search(table, key);

  if (entry) {
    free(entry->value.variable.name);
    free(entry->value.variable.type);
    entry->value.variable.name = strdup(name);
    entry->value.variable.type = strdup(type);
    return;
  }

  if (table->size == table->capacity) {
    ST_Resize(table);
  }

  entry = &table->entries[table->size++];
  entry->key = strdup(key);
  entry->type = VAR;
  entry->value.variable.name = strdup(name);
  entry->value.variable.type = strdup(type);
}

void ST_InsertFunction(ST *table, const char *key, const char *name, const char *returnType) {
  STE *entry = ST_Search(table, key);

  if (entry) {
    free(entry->value.function.name);
    free(entry->value.function.returnType);
    entry->value.function.name = strdup(name);
    entry->value.function.returnType = strdup(returnType);
    return;
  }

  if (table->size == table->capacity) {
    ST_Resize(table);
  }

  entry = &table->entries[table->size++];
  entry->key = strdup(key);
  entry->type = FUNC;
  entry->value.function.name = strdup(name);
  entry->value.function.returnType = strdup(returnType);
}

void ST_Print(ST *table) {
  printf("Symbol Table:\n");
  printf("Capacity: %d, Size: %d\n", table->capacity, table->size);
  for (int i = 0; i < table->size; i++) {
    printf("Index %d: Key = %s, Type = ", i, table->entries[i].key);

    switch (table->entries[i].type) {
      case CONSTANT:
        printf("CONSTANT, Type = %s\n", table->entries[i].value.constant.type);
        break;
      case VAR:
        printf("VARIABLE, Name = %s, Type = %s\n", table->entries[i].value.variable.name, table->entries[i].value.variable.type);
        break;
      case FUNC:
        printf("FUNCTION, Name = %s, Return Type = %s\n", table->entries[i].value.function.name, table->entries[i].value.function.returnType);
        break;
    }
  }
}

ST* ST_BuildFromFAST(AST *node) {
  ST *st = ST_Create(16);
  ST_Walker(st, node);
  return st;
}

void ST_Walker(ST *st, AST *node) {
  if (TOKEN_CONVERTS_TO_INT(node)) {
    // const char *key = RANDOM_KEY();
    // ST_InsertConstant(st, key, type);
  }

  if (TOKEN_IS(node, "AST_VAR_DEC")) {
    // const char *varName = AST_GetChild(node, 1)->token;
    // const char *varType = AST_GetType(node);
    // const char *key = RANDOM_KEY();
    // ST_InsertVariable(st, key, varName, varType);
  }

  if (TOKEN_IS(node, "AST_FUNC_DEF")) {
    // const char *funcName = AST_GetChild(node, 0)->token;
    // const char *returnType = AST_GetType(node);
    // const char *key = RANDOM_KEY();
    // ST_InsertFunction(st, key, funcName, returnType);
  }

  for (int i = 0; i < node->childCount; i++) {
    AST *child = AST_GetChild(node, i);
    ST_Walker(st, child);
  }
}
