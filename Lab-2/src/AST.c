#include "AST.h"

AST* createNode(uint32_t id, char* token) {
    AST* node = (AST*)malloc(sizeof(AST));

    if (node == NULL) {
        fprintf(stderr, "AST: Memory allocation failed\n");
        return NULL;
    }

    node->parent = NULL;
    node->children = NULL;
    node->child_count = 0;
    node->id = id;
    node->token = strdup(token);
    return node;
}

size_t getChildCount(AST* node) {
    if (node == NULL) {
        return 0;
    }
    return node->child_count;
}

char* getToken(AST* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->token;
}

void addChild(AST* parent, AST* child) {
    if (parent == NULL || child == NULL) {
        return;
    }

    parent->children = (AST**)realloc(parent->children, sizeof(AST*) * (parent->child_count + 1));
    if (parent->children == NULL) {
        fprintf(stderr, "AST addChild memory allocation failed\n");
        return;
    }
    parent->child_count++;
    parent->children[parent->child_count-1] = child;
    child->parent = parent;

}

void freeAST(AST* node) {
    if (node == NULL) return;
    free(node->token);

    for (size_t i = 0; i < node->child_count; i++) {
        freeAST(node->children[i]);
    }

    free(node->children);
    free(node);
}

AST* findNodeById(AST* node, uint32_t id) {
    if (node == NULL) {
        return NULL;
    }
    if (node->id == id) {
        return node;
    }

    for (size_t i = 0; i < node->child_count; i++) {
        AST* foundNode = findNodeById(node->children[i], id);
        if (foundNode != NULL) {
            return foundNode;
        }
    }

    return NULL;
}

AST* getChild(AST* parent, size_t i) {
    if (parent == NULL || i >= parent->child_count) {
        return NULL;
    }
    return parent->children[i];
}

AST* getParent(AST* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->parent;
}

void outputASTEdges(AST* node, FILE* file) {
    for (int i = 0; i < node->child_count; i++) {
        AST* child = getChild(node, i);
        writeEdge(node, child, 0, file);
        outputASTEdges(child, file);
    }
}

void printAST(AST* head, FILE* file) {
    fprintf(file, "digraph AST {\n"); //NOLINT
    fprintf(file, "    node [shape=box];\n"); //NOLINT
    outputAST(head, file);
    outputASTEdges(head, file);
    fprintf(file, "}\n");
}

void outputAST(AST* node, FILE* file) {
    if (node == NULL) return;
    printf("Visiting node: %s\n", node->token);
    writeNode(node, 0, file);
    for (int i = 0; i < node->child_count; i++) {
        AST* child = getChild(node, i);
        outputAST(child, file);
    }
}



AST* buildFromParseResult(pParseResult parseResult) {
    AST* head = createNode(parseResult->p->adaptor->getUniqueID(parseResult->p->adaptor,
                                                                parseResult->sr.tree),
                           (char*)parseResult->sr.tree->getText(parseResult->sr.tree)->chars);
    int child_count = parseResult->sr.tree->getChildCount(parseResult->sr.tree);
    //head->child_count = child_count;
    for(int i = 0; i < child_count; i++) {
        //start process for a i-th child
        setChildFromAntlrNode(head, parseResult->p->adaptor,
                           parseResult->sr.tree->getChild(parseResult->sr.tree, i));
    }

    return head;
}

void setChildFromAntlrNode(AST* parent, pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE node) {
    if (node == NULL) {
        return;
    }
    AST* child = createNode(adaptor->getUniqueID(adaptor, node),
                            (char*)node->getText(node)->chars);
    addChild(parent, child);

    int child_count = node->getChildCount(node);
    for (int i = 0; i < child_count; i++) {
        pANTLR3_BASE_TREE child_node = node->getChild(node, i);
        setChildFromAntlrNode(child, adaptor, child_node);
    }
}

void writeNode(AST* node, int basicBlockIndex, FILE *file) {
    fprintf(file, "    cluster_%d_node%u [label=\"%s\"];\n", basicBlockIndex,
                                                             node->id, node->token); //NOLINT
}

void writeEdge(AST* parent, AST* child, int basicBlockIndex, FILE *file) {
    fprintf(file, "    cluster_%d_node%u -> cluster_%d_node%u;\n",
            basicBlockIndex, parent->id, basicBlockIndex, child->id); //NOLINT
}

void outputOpNode(AST* node, int basicBlockIndex, FILE *file) {
    if (node == NULL) return;

    char* name = node->token;
    printf("Visiting node: %s\n", name);
    int childCount = node->child_count;

    writeNode(node, basicBlockIndex, file);
    for (int i = 0; i < childCount; i++) {
        outputOpNode(node, basicBlockIndex, file);
    }
}

void outputOpEdge(AST* parent, AST* child, int basicBlockIndex, FILE *file) {
    char* name = parent->token;
    printf("Visiting node: %s\n", name);
    int childCount = parent->child_count;

    for (int i = 0; i < childCount; i++) {
        AST* child = getChild(parent, i);

        writeEdge(parent, child, basicBlockIndex, file);
        outputOpEdge(parent, child, basicBlockIndex, file);
    }
}

pANTLR3_BASE_TREE analyzeOp (pParseResult parseResult,
                            pANTLR3_BASE_TREE node) {
    pANTLR3_BASE_TREE head = (pANTLR3_BASE_TREE)parseResult->p->adaptor->dupTree(parseResult->p->adaptor,
                                                                                   node);

    if(strcmp((char*)node->getText(node)->chars, "CALL") == 0) {
        if(parseResult->p->adaptor->getChild(parseResult->p->adaptor, head,  1)) {
            pANTLR3_BASE_TREE readNode = (pANTLR3_BASE_TREE) parseResult->p->adaptor->dupNode(parseResult->p->adaptor, NULL);
            parseResult->p->adaptor->getText(parseResult->p->adaptor, readNode);
        }
        else {
            printf("not lol\n");
        }
    }
    return head;
}

void analyzeCall(pANTLR3_BASE_TREE_ADAPTOR adaptor,
                 pANTLR3_BASE_TREE node) {

}
