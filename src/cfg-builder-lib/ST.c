#include "safe_mem.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ST.h"

ST* ST_Create(int capacity) {
  ST* table = (ST*)safe_malloc(sizeof(ST));
  table->capacity = capacity;
  table->size = 0;
  table->entries = (STE*)safe_malloc(capacity * sizeof(STE));
  return table;
}

void ST_Free(ST *table) {
  for (int i = 0; i < table->size; i++) {
    switch (table->entries[i].type) {
      case ST_CONSTANT:
        free(table->entries[i].value.constant.value);
        free(table->entries[i].value.constant.type);
        break;
      case ST_VAR:
        free(table->entries[i].value.variable.name);
        free(table->entries[i].value.variable.type);
        break;
      case ST_FUNC:
        free(table->entries[i].value.function.name);
        free(table->entries[i].value.function.returnType);
        break;
    }
  }
  free(table->entries);
  free(table);
}

void ST_Resize(ST* table) {
  int new_capacity = table->capacity * 2;
  STE* new_entries = (STE*)safe_malloc(new_capacity * sizeof(STE));

  for (int i = 0; i < table->size; i++) {
    new_entries[i] = table->entries[i];
  }

  free(table->entries);
  table->entries = new_entries;
  table->capacity = new_capacity;
}

STE* ST_Search(ST* table, const char* name, VT valueType) {
  for (int i = 0; i < table->size; i++) {
    if (table->entries[i].type == valueType) {
      switch (valueType) {
        case ST_VAR:
          if (strcmp(table->entries[i].value.variable.name, name) == 0)
            return &table->entries[i];
          break;
        case ST_FUNC:
          if (strcmp(table->entries[i].value.function.name, name) == 0)
            return &table->entries[i];
          break;
        case ST_CONSTANT:
          if (strcmp(table->entries[i].value.constant.value, name) == 0)
            return &table->entries[i];
          break;
      }
    }
  }
  return NULL;
}

void ST_InsertConstant(ST* table, const char* value, const char* type) {
  if (ST_Search(table, value, ST_CONSTANT)) {
    return;
  }

  if (table->size == table->capacity) {
    ST_Resize(table);
  }

  STE* entry = &table->entries[table->size++];
  entry->type = ST_CONSTANT;
  entry->value.constant.value = strdup(value);
  entry->value.constant.type = strdup(type);
}

void ST_InsertVariable(ST* table, const char* name, const char* type) {
  if (ST_Search(table, name, ST_VAR)) {
    return;
  }

  if (table->size == table->capacity) {
    ST_Resize(table);
  }

  STE* entry = &table->entries[table->size++];
  entry->type = ST_VAR;
  entry->value.variable.name = strdup(name);
  entry->value.variable.type = strdup(type);
}

void ST_InsertFunction(ST* table, const char* name, const char* returnType) {
  if (ST_Search(table, name, ST_FUNC)) {
    return;
  }

  if (table->size == table->capacity) {
    ST_Resize(table);
  }

  STE* entry = &table->entries[table->size++];
  entry->type = ST_FUNC;
  entry->value.function.name = strdup(name);
  entry->value.function.returnType = strdup(returnType);
}


void ST_Print(ST *table) {
  printf("Symbol Table:\n");
  printf("Capacity: %d, Size: %d\n", table->capacity, table->size);
  for (int i = 0; i < table->size; i++) {
    printf("Index %d: Key = %u, Type = ", i, table->entries[i].key);

    switch (table->entries[i].type) {
      case ST_CONSTANT:
        printf("CONSTANT, Value = %s, = Type = %s\n", table->entries[i].value.constant.value,
                                                      table->entries[i].value.constant.type);
        break;
      case ST_VAR:
        printf("VARIABLE, Name = %s, Type = %s\n", table->entries[i].value.variable.name,
                                                   table->entries[i].value.variable.type);
        break;
      case ST_FUNC:
        printf("FUNCTION, Name = %s, Return Type = %s\n", table->entries[i].value.function.name,
                                                          table->entries[i].value.function.returnType);
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
  if (AST_TOKEN_CONVERTS_TO_INT(node))
    ST_InsertConstant(st, node->token, "int");

  if (AST_TOKEN_IS(node, "AST_VAR_DEC") ||
      AST_TOKEN_IS(node, "AST_VAR_DEF"))
  {
    const char* varType = AST_GetChild(node, 0)->token;
    const char* varName = AST_GetChild(node, 1)->token;

    ST_InsertVariable(st, varName, varType);
  }

  for (int i = 0; i < node->childCount; i++) {
    AST *child = AST_GetChild(node, i);
    ST_Walker(st, child);
  }
}
