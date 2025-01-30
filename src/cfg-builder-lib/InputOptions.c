#include "InputOptions.h"
#include "AST.h"
#include "Functions.h"
#include "CFGOutput.h"
#include "commands.h"
#include "ASMGen.h"

void processInput(int argc, char** argv) {
  const char* outputDir = argv[1];

  struct stat st = {0};
  if (stat(outputDir, &st) == -1) {
    if (mkdir(outputDir, 0777) == -1) {
      perror("PI :: ERROR :: FAILED TO CREATE OUTPUT DIRECTORY\n");
      return;
    }
  }

  for (int i = 2; i < argc; ++i) { //for each file
    char* filename = getBaseName(argv[i]);
    char* outputSubDir = createFilePath("%s/%s", outputDir, filename);
    mkdir(outputSubDir, 0777);

    char *inputText = readFileToString(argv[i]);
    PR* parseResult = parse(inputText);
    AST* ast = AST_BuildFromParseResult(parseResult);
    FL* functionList = FL_FindFsInAST(ast, argv[i]);
    AS* addrSet = AS_init();
    if(!functionList->count) {
      perror("PI :: WARNING :: NO FUNCTIONS DETECTED\n");
      free(functionList);
      free(filename);
      return;
    }

    for(int j = 0; j < functionList->count; j++) {
      char* cfgDotFilename = createFilePath("%s/cfg/%s-cfg.dot", outputSubDir, functionList->functions[j]->name);
      FILE* cfgFile = open_file(cfgDotFilename, "w");
      CFG_WriteInFile(functionList->functions[j]->cfg, cfgFile);
      close_file(cfgFile);

      char* asmListingFilename = createFilePath("%s/asm/%s-asm-listing.txt", outputSubDir, functionList->functions[j]->name);
      FILE* asmFile = open_file(asmListingFilename, "w");
      ASM_GenerateListing(addrSet, functionList->functions[j], asmFile);
      close_file(asmFile);

      char* cfgPngFilename = createFilePath("%s/cfg/%s-cfg.png", outputSubDir, functionList->functions[j]->name);
      executeCommand("dot -Tpng %s -o %s", cfgDotFilename, cfgPngFilename);
      executeCommand("xdg-open %s", cfgPngFilename);
      free(cfgPngFilename);
      free(cfgDotFilename);
    }
    free(inputText);
    cleanup(parseResult);
    free(filename);
    free(outputSubDir);
    FL_Free(functionList);
    AST_Free(ast);
  }
}

