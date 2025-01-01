#ifndef OT_H
#define OT_H


typedef enum {
  OT_OPERATOR,
  OT_OPERAND,
  OT_CALL,
  OT_LITERAL,
  OT_PLACE
} OT_t;

typedef enum {
  OT_BOOL,
  OT_BYTE,
  OT_INT,
  OT_UINT,
  OT_LONG,
  OT_ULONG,
  OT_CHAR,
  OT_STRING
} DataType;

typedef struct OT {
  OT_t type;
  DataType dataType;
  char operator;
  union {
    int intValue;
    unsigned int uintValue;
    long longValue;
    unsigned long ulongValue;
    char charValue;
    char* stringValue;
    int boolValue;
    unsigned char byteValue;
    char* identifier;
  } value;
  struct OT* left;
  struct OT* right;
  struct OT** children;
  int childCount;
} OT;

#endif
