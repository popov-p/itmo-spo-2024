#pragma once
#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75

typedef enum { INT_CONST, STR_CONST, VAR_NAME, FUNC_NAME } VT; // Value Type

typedef struct {
  char *key;
  VT type;
  union {
    int intConst;
    char *strConst;
    char *varName;
    char *funcName;
  } value;
} STE; // Symbol Table element

typedef struct {
  STE *entries;
  int capacity;
  int size;
} ST; //Symbol Table

ST *ST_Create(int capacity);
void ST_Free(ST *table);
void ST_Resize(ST *table);

void ST_InsertInt(ST *table, int value);
void ST_InsertStr(ST *table, const char *value);
void ST_InsertVar(ST *table, const char *varName);
void ST_InsertFunc(ST *table, const char *funcName);
STE* ST_SearchByValue(ST *table, const void *value, VT type);
void ST_ResizeTable(ST *table);
void ST_Print(ST *table);
