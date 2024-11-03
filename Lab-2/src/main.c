#include <antlr3.h>
#include "InputOptions.h"

int main(int argc, char *argv[]) {
    char *emulatedArgs[] = {
        "cfgbuilder-stub-name",
        "../output",
        "../input/prog-1.txt"
    };

    int emulatedArgc = sizeof(emulatedArgs) / sizeof(emulatedArgs[0]);
    processInput(emulatedArgc, emulatedArgs);
    return 0;
}
