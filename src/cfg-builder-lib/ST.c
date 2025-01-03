#include "safe_mem.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ST.h"

#define INITIAL_CAPACITY 16
#define RANDOM_KEY() ({ \
    unsigned int key = arc4random(); \
    char *key_str = (char *)malloc(11 * sizeof(char)); \
    snprintf(key_str, 11, "%u", key); \
    key_str; \
})

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
    if (table->entries[i].type == STR_CONST ||
        table->entries[i].type == VAR_NAME ||
        table->entries[i].type == FUNC_NAME) {
      free(table->entries[i].value.strConst);
    }
  }
  free(table->entries);
  free(table);
}

void ST_Resize(ST *table) {
  int new_capacity = table->capacity * 2;
  STE *new_entries = (STE *)safe_malloc(new_capacity * sizeof(STE));

  for (int i = 0; i < table->size; i++) {
    new_entries[i] = table->entries[i];
  }

  free(table->entries);
  table->entries = new_entries;
  table->capacity = new_capacity;
}

STE *ST_SearchByValue(ST *table, const void *value, VT type) {
  for (int i = 0; i < table->size; i++) {
    if (table->entries[i].type != type) {
      continue;
    }

    switch (type) {
      case INT_CONST:
        if (table->entries[i].value.intConst == *(int *)value) {
          return &table->entries[i];
        }
        break;
      case STR_CONST:
      case VAR_NAME:
      case FUNC_NAME:
        if (strcmp(table->entries[i].value.strConst, (char *)value) == 0) {
          return &table->entries[i];
        }
        break;
    }
  }
  return NULL;
}

void ST_InsertInt(ST *table, int value) {
  STE *entry = ST_SearchByValue(table, &value, INT_CONST);

  if (entry) {
    entry->value.intConst = value;
    return;
  }

  if (table->size == table->capacity) {
    ST_Resize(table);
  }

  entry = &table->entries[table->size++];
  entry->key = RANDOM_KEY();
  entry->type = INT_CONST;
  entry->value.intConst = value;
}

void ST_InsertStr(ST *table, const char *value) {
  STE *entry = ST_SearchByValue(table, value, STR_CONST);

  if (entry) {
    free(entry->value.strConst);
    entry->value.strConst = strdup(value);
    return;
  }

  if (table->size == table->capacity)
    ST_Resize(table);

  entry = &table->entries[table->size++];
  entry->key = RANDOM_KEY();
  entry->type = STR_CONST;
  entry->value.strConst = strdup(value);
}

void ST_InsertVar(ST *table, const char *varName) {
  STE *entry = ST_SearchByValue(table, varName, VAR_NAME);

  if (entry) {
    free(entry->value.varName);
    entry->value.varName = strdup(varName);
    return;
  }

  if (table->size == table->capacity)
    ST_Resize(table);

  entry = &table->entries[table->size++];
  entry->key = RANDOM_KEY();
  entry->type = VAR_NAME;
  entry->value.varName = strdup(varName);
}

void ST_InsertFunc(ST *table, const char *funcName) {
  STE *entry = ST_SearchByValue(table, funcName, FUNC_NAME);

  if (entry) {
    free(entry->value.funcName);
    entry->value.funcName = strdup(funcName);
    return;
  }

  if (table->size == table->capacity)
    ST_Resize(table);

  entry = &table->entries[table->size++];
  entry->key = RANDOM_KEY();
  entry->type = FUNC_NAME;
  entry->value.funcName = strdup(funcName);
}

void ST_Print(ST *table) {
  printf("Symbol Table:\n");
  printf("Capacity: %d, Size: %d\n", table->capacity, table->size);
  for (int i = 0; i < table->size; i++) {
    printf("Index %d: Key = %s, Type = ", i, table->entries[i].key);

    switch (table->entries[i].type) {
      case INT_CONST:
        printf("INT, Value = %d\n", table->entries[i].value.intConst);
        break;
      case STR_CONST:
        printf("STR, Value = %s\n", table->entries[i].value.strConst);
        break;
      case VAR_NAME:
        printf("VAR, Name = %s\n", table->entries[i].value.varName);
        break;
      case FUNC_NAME:
        printf("FUNC, Name = %s\n", table->entries[i].value.funcName);
        break;
    }
  }
}
