#include "InputOptions.h"
#include "ST.h"
int main(int argc, char **argv) {
  ST *table = ST_Create(4);
  printf("Created Symbol Table with initial capacity 4.\n\n");

  printf("Inserting constants...\n");
  ST_InsertConstant(table, "C1", "int");
  ST_InsertConstant(table, "C2", "float");

  printf("Inserting variables...\n");
  ST_InsertVariable(table, "V1", "var1", "int");
  ST_InsertVariable(table, "V2", "var2", "string");

  printf("Inserting functions...\n");
  ST_InsertFunction(table, "F1", "func1", "void");
  ST_InsertFunction(table, "F2", "func2", "int");

  printf("\nSearching for entries...\n");
  STE *entry;

  entry = ST_Search(table, "C1");
  if (entry) {
    printf("Found constant with key 'C1': Type = %s\n", entry->value.constant.type);
  } else {
    printf("Constant with key 'C1' not found.\n");
  }

  entry = ST_Search(table, "V2");
  if (entry) {
    printf("Found variable with key 'V2': Name = %s, Type = %s\n", entry->value.variable.name, entry->value.variable.type);
  } else {
    printf("Variable with key 'V2' not found.\n");
  }

  entry = ST_Search(table, "F1");
  if (entry) {
    printf("Found function with key 'F1': Name = %s, Return Type = %s\n", entry->value.function.name, entry->value.function.returnType);
  } else {
    printf("Function with key 'F1' not found.\n");
  }

  printf("\nPrinting the Symbol Table:\n");
  ST_Print(table);

  ST_Free(table);
  printf("\nSymbol Table memory freed.\n");

  processInput(argc, argv);
  return 0;
}
