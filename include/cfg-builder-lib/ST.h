#pragma once
#include "AST.h"

#define INITIAL_CAPACITY 256
#define LOAD_FACTOR 0.75

#define TOKEN_TO_INT(node) atoi(node->token)

typedef enum { ST_CONSTANT, ST_VAR, ST_FUNC } VT; // Value Type

typedef struct {
  uint32_t key;
  VT type;
  union {
    struct {
      char* value;
      char* type;
    } constant;
    struct {
      char* name;
      char* type;
    } variable;
    struct {
      char* name;
      char* returnType;
    } function;
  } value;
  uint16_t addr;
} STE; // Symbol Table element

typedef struct {
  STE *entries;
  int capacity;
  int size;
} ST; // Symbol Table

ST* ST_Create(int capacity);
void ST_Free(ST* table);
void ST_Resize(ST* table);

STE* ST_Search(ST* table, const char* name, VT valueType);

void ST_InsertConstant(ST* table,
                       const char* value,
                       const char* type);

void ST_InsertVariable(ST* table,
                       const char* name,
                       const char* type);

void ST_InsertFunction(ST* table,
                       const char* name,
                       const char* returnType);

void ST_Print(ST* table);
ST* ST_BuildFromFAST(AST* node);
void ST_Walker(ST* st, AST* node);
