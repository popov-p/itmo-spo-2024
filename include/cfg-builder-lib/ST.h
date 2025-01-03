#pragma once
#include "AST.h"

#define INITIAL_CAPACITY 256
#define LOAD_FACTOR 0.75

#define TOKEN_CONVERTS_TO_INT(node) ({            \
    char* endptr;                                 \
    strtol((node)->token, &endptr, 10);           \
    (*endptr == '\0');                            \
})
#define TOKEN_TO_INT(node) atoi(node->token)

typedef enum { CONSTANT, VAR, FUNC } VT; // Value Type

typedef struct {
  char *key;
  VT type;
  union {
    struct {
      char* type;
    } constant;
    struct {
      char *name;
      char* type;
    } variable;
    struct {
      char* name;
      char* returnType;
    } function;
  } value;
} STE; // Symbol Table element

typedef struct {
  STE *entries;
  int capacity;
  int size;
} ST; //Symbol Table

ST *ST_Create(int capacity);
void ST_Free(ST* table);
void ST_Resize(ST* table);

STE* ST_Search(ST *table, const char *key);
void ST_InsertConstant(ST *table, const char *key, const char *type);
void ST_InsertVariable(ST *table, const char *key, const char *name, const char *type);
void ST_InsertFunction(ST *table, const char *key, const char *name, const char *returnType);

void ST_Print(ST* table);
ST* ST_BuildFromFAST(AST *node);
void ST_Walker(ST* st, AST* node);
