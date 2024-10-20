#include "OpTree.h"
#include "HashTree.h"

AST* createNode(uint32_t id, const char* token) {
    AST* node = (AST*)malloc(sizeof(AST));

    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    node->parent = NULL;
    node->children = NULL;
    node->numChildren = 0;
    node->token = strdup(token);
    return node;
}

size_t getChildCount(AST* node) {
    if (node == NULL) {
        return 0;
    }
    return node->numChildren;
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

    parent->children = (AST**)realloc(parent->children, sizeof(AST*) * (parent->numChildren + 1));
    if (parent->children == NULL) {
        fprintf(stderr, "OpTree addChild memory allocation failed\n");
        return;
    }

    parent->children[parent->numChildren] = child;
    child->parent = parent;
    parent->numChildren++;
}

void freeTree(AST* node) {
    if (node == NULL) return;
    free(node->token);

    for (size_t i = 0; i < node->numChildren; i++) {
        freeTree(node->children[i]);
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

    for (size_t i = 0; i < node->numChildren; i++) {
        AST* foundNode = findNodeById(node->children[i], id);
        if (foundNode != NULL) {
            return foundNode;
        }
    }

    return NULL;
}



















void writeNode(pANTLR3_BASE_TREE tree, uint32_t* id, int basicBlockIndex, FILE *file) {
    fprintf(file, "    cluster_%d_node%u [label=\"%s\"];\n", basicBlockIndex,
             *id, (char *)tree->toString(tree)->chars); //NOLINT
}

void writeEdge(uint32_t* parentId, uint32_t* childId, int basicBlockIndex, FILE *file) {
    fprintf(file, "    cluster_%d_node%u -> cluster_%d_node%u;\n",
            basicBlockIndex, *parentId, basicBlockIndex, *childId); //NOLINT
}

void outputOpNode(pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE node, int basicBlockIndex, FILE *file) {
    if (adaptor == NULL) return;
    if (node == NULL) return;

    char* name = (char*)adaptor->getText(adaptor, node)->chars;
    uint32_t current_id = adaptor->getUniqueID(adaptor, node);
    printf("Visiting node: %s\n", name);
    int childCount = node->getChildCount(node);

    writeNode(node, &current_id, basicBlockIndex, file);
    for (int i = 0; i < childCount; i++) {
        pANTLR3_BASE_TREE child = adaptor->getChild(adaptor, node, i);
        outputOpNode(adaptor, child, basicBlockIndex, file);
    }
}


void outputOpEdge(pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE node, int basicBlockIndex, FILE *file) {
    char* name = (char*)adaptor->getText(adaptor, node)->chars;
    uint32_t current_id = adaptor->getUniqueID(adaptor, node);
    printf("Visiting node: %s\n", name);
    int childCount = node->getChildCount(node);

    for (int i = 0; i < childCount; i++) {
        pANTLR3_BASE_TREE childNode = node->getChild(node, i);
        uint32_t child_id = adaptor->getUniqueID(adaptor, childNode);

        writeEdge(&current_id, &child_id, basicBlockIndex, file);
        outputOpEdge(adaptor, childNode, basicBlockIndex, file);
    }
}

void outputSubgraph(pParseResult parseResult, CFG* cfg, int basicBlockIndex, FILE* file) {
    fprintf(file, "subgraph cluster_%d {\n", basicBlockIndex);
    fprintf(file, "    label=\"%s%d\";\n", "BB", basicBlockIndex);
    BasicBlock* bb = cfg->blocks[basicBlockIndex];
    pANTLR3_BASE_TREE result = analyzeOp(parseResult, getNodeByUniqueID(bb->id));

    outputOpNode(parseResult->p->adaptor, result, basicBlockIndex, file);
    outputOpEdge(parseResult->p->adaptor, result, basicBlockIndex, file);
    fprintf(file, "}\n");
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
