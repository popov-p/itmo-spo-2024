#include "InputOptions.h"
#include "AST.h"
#include "Functions.h"
#include "CFGOutput.h"
#include "commands.h"

void processInput(int argc, char** argv) {
  const char* outputDir = argv[1];

  struct stat st = {0};
  if (stat(outputDir, &st) == -1) {
    if (mkdir(outputDir, 0777) == -1) {
      perror("PI :: ERROR :: FAILED TO CREATE OUTPUT DIRECTORY");
      return;
    }
  }

  for (int i = 2; i < argc; ++i) { //for each file
    char* filename = getBaseName(argv[i]);
    char* outputSubDir = createFilePath("%s/%s", outputDir, filename);
    mkdir(outputSubDir, 0777);

    char *inputText = readFileToString(argv[i]);
    ParseResult* parseResult = parse(inputText);
    AST* head = AST_BuildFromParseResult(parseResult);

    FunctionList* functionList = findFunctions(head, argv[i]);

    if(!functionList->count) {
      perror("PI :: WARNING :: NO FUNCTIONS DETECTED\n");
      free(functionList);
      free(filename);
      return;
    }

    for(int j = 0; j < functionList->count; j++) {
      char* cfgDotFilename = createFilePath("%s/%s-cfg.dot", outputSubDir, functionList->items[j]->name);
      FILE *cfgFile = fopen(cfgDotFilename, "w");
      if (!cfgFile)
        fprintf(stderr, "PI :: ERROR :: FILE NOT OPENED");
      else {
        CFG_WriteInFile(functionList->items[j]->cfg, cfgFile);
        fclose(cfgFile);
      }
      char* cfgPngFilename = createFilePath("%s/%s-cfg.png", outputSubDir, functionList->items[j]->name);
      executeCommand("dot -Tpng %s -o %s", cfgDotFilename, cfgPngFilename);
      executeCommand("xdg-open %s", cfgPngFilename);
      free(cfgPngFilename);
      free(cfgDotFilename);
    }
    free(inputText);
    cleanup(parseResult);
    free(filename);
    free(outputSubDir);
    freeFunctionList(functionList);
    AST_Free(head);
  }
}

