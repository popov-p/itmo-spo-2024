#pragma once
#include "AST.h"
#include "stdbool.h"
#include "ST.h"

#define __READ  "OP_READ"
#define __WRITE  "OP_WRITE"
#define __PLACE "OP_PLACE"
#define __CONST "OP_CONST"
#define __CALL "OP_CALL"
#define __HEAD "OP_HEAD"
#define __PLUS "OP_PLUS"

#define IS_OPERATION(node, op) ((node)->dataType == OT_OPERATION && strcmp((node)->data.operation.operationType, (op)) == 0)
#define IS_CONSTANT(node) ((node)->dataType == OT_CONSTANT)
#define IS_VARIABLE(node) ((node)->dataType == OT_VARIABLE)



static inline bool OT_IsInt(const char* token) {
  if (!token || *token == '\0') {
    return false;
  }
  if (*token == '-' || *token == '+') {
    token++;
  }
  while (*token) {
    if (!isdigit((unsigned char)*token)) {
      return false;
    }
    token++;
  }
  return true;
}

typedef enum OT_t {OT_OPERATION, OT_VARIABLE, OT_FUNCTION, OT_CONSTANT, OT_AUX} OT_t;
typedef struct OT {
  OT_t dataType;
  struct OT* parent;
  struct OT** children;
  int childCount;
  uint32_t id;
  union {
    struct {
      char* returnType;
      char* operationType;
    } operation;
    struct {
      char* name;
      char* varType;
    } variable;
    struct {
      char* name;
      char* returnType;
    } function;
    struct {
      char* value;
      char* constType;
    } constant;
    struct {
      char* firstOption;
      char* secondOption;
    } auxiliary;
  } data;
} OT;


OT* OT_CreateNode(AST* astNode,
                  OT_t dataType,
                  const char* primaryData,
                  const char* secondaryData);

OT* OT_CreateAuxiliaryNode(OT_t dataType,
                           const char* primaryData,
                           const char* secondaryData);



void OT_AddChild(OT* parent, OT* child);
void OT_RemoveChild(OT* parent, OT* child);
void OT_InsertBetween(OT* parent, OT* thatChild, OT* thisNode);
OT* OT_BuildFromAST(ST* st, AST* node);

OT* OT_GetChild(const OT* parent, int index);

void OT_Walker(OT* ot, ST* st, AST* node);
void OT_TypeResolver(OT* ot);
void OT_Free(OT* node);


char* OT_ASTToOpToken(const char* astToken);
