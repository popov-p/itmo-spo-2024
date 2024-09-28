#include "Treebuilder.h"

char* readFileToString(const char* filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("not ok. error opening file\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        perror("not ok. memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    fclose(file);
    return buffer;
}

pParseResult parse(const char* text) {
    pParseResult result = (ParseResult*)malloc(sizeof(ParseResult));

    result->is = antlr3StringStreamNew((pANTLR3_UINT8)text,
                                       ANTLR3_ENC_8BIT, strlen(text),
                                       (pANTLR3_UINT8)"input string");
    result->l = Var4LexerNew(result->is);
    result->ts = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(result->l));
    result->p = Var4ParserNew(result->ts);
    result->sr = result->p->source(result->p);
    return result;
}

void generateDot(pParseResult result, const char* path) {
    pANTLR3_BASE_TREE_ADAPTOR treeAdaptor = result->p->adaptor;
    pANTLR3_STRING dotString = treeAdaptor->makeDot(treeAdaptor, result->sr.tree);

    FILE *dotFile = fopen(path, "w");
    if (dotFile != NULL) {
        fprintf(dotFile, "%s", (char *)dotString->chars);
        fclose(dotFile);
    } else {
        printf("not ok. trouble with opening .dot file\n");
    }
}

int cleanup(ParseResult* pr) {
    if (pr->p != NULL) {
        pr->p->free(pr->p);
    }
    if (pr->ts != NULL) {
        pr->ts->free(pr->ts);
    }
    if (pr->l != NULL) {
        pr->l->free(pr->l);
    }
    if (pr->is != NULL) {
        pr->is->close(pr->is);
    }
    if (pr == NULL) {
        return 1;
    }
    else {
        free(pr);
    }
    return 0;
}
