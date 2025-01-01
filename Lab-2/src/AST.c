#include "AST.h"

#include <stdlib.h>
#include <stdint.h>

AST* createNode(uint32_t id, char* token) {
    AST* node = (AST*)malloc(sizeof(AST));

    if (!node) {
        fprintf(stderr, "ERROR :: MALLOC FAIL\n");
        return NULL;
    }

    node->parent = NULL;
    node->children = NULL;
    node->childCount = 0;
    node->id = id;
    node->token = strdup(token);
    return node;
}

void printTree(AST* node, int level) {
    if (!node)
        return;
    for (int i = 0; i < level; i++)
        printf("  ");
    printf("PT :: ID - %d, TOKEN - %s\n", node->id, node->token);

    for (size_t i = 0; i < node->childCount; i++)
        printTree(node->children[i], level + 1);
}

void addChild(AST* parent, AST* child) {
    if (!parent)
        return;
    if (!child)
        return;

    parent->children = (AST**)realloc(parent->children, sizeof(AST*) * (parent->childCount + 1));
    if (!parent->children) {
        fprintf(stderr, "ERROR :: REALLOC FAILED\n");
        return;
    }
    parent->childCount++;
    parent->children[parent->childCount-1] = child;
    child->parent = parent;
}

void freeAST(AST* node) {
    if (!node)
        return;
    free(node->token);

    for (size_t i = 0; i < node->childCount; i++)
        freeAST(node->children[i]);

    free(node->children);
    free(node);
}

AST* findNodeById(AST* node, uint32_t id) {
    if (!node)
        return NULL;
    if (node->id == id)
        return node;

    for (size_t i = 0; i < node->childCount; i++) {
        AST* foundNode = findNodeById(node->children[i], id);
        if (foundNode)
            return foundNode;
    }

    return NULL;
}

AST* getChild(AST* parent, size_t i) {
    if (!parent || i >= parent->childCount) {
        return NULL;
    }
    return parent->children[i];
}

void outputASTEdges(AST* node, FILE* file) {
    for (size_t i = 0; i < node->childCount; i++) {
        AST* child = getChild(node, i);
        writeEdge(node, child, 0, file);
        outputASTEdges(child, file);
    }
}

void printAST(AST* head, FILE* file) {
    fprintf(file, "digraph AST {\n");
    fprintf(file, "    node [shape=box];\n");
    outputAST(head, file);
    outputASTEdges(head, file);
    fprintf(file, "}\n");
}

void outputAST(AST* node, FILE* file) {
    if (node == NULL) return;
    //printf("VISIT:: %s\n", node->token);
    writeNode(node, 0, file);
    for (size_t i = 0; i < node->childCount; i++) {
        AST* child = getChild(node, i);
        outputAST(child, file);
    }
}

void insertBetween(AST* parent, AST* thatChild, AST* thisNode) {
    if (parent == NULL || thatChild == NULL || thisNode == NULL)
        return;

    if (thatChild->parent != parent)
        return;

    thisNode->children = (AST**)malloc(sizeof(AST*));
    if(!thisNode->children) {
        fprintf(stderr, "ERROR :: MALLOC FAILED\n");
        return;
    }
    thisNode->children[0] = thatChild;
    thisNode->childCount = 1;
    thatChild->parent = thisNode;

    for (size_t i = 0; i < parent->childCount; i++) {
        if (parent->children[i] == thatChild) {
            parent->children[i] = thisNode;
            break;
        }
    }
    thisNode->parent = parent;
}


AST* duplicateTree(AST* head) {
    if (!head)
        return NULL;

    AST* newNode = createNode(head->id, head->token);

    for (size_t i = 0; i < head->childCount; i++) {
        AST* childCopy = duplicateTree(head->children[i]);
        addChild(newNode, childCopy);
    }

    return newNode;
}


AST* duplicateLeftSubtree(AST* head) {
    if (!head)
        return NULL;
    AST* newHead = createNode(head->id, head->token);
    if (!newHead)
        return NULL;
    if (head->childCount > 0 && head->children[0]) {
        AST* leftChildCopy = duplicateTree(head->children[0]);
        addChild(newHead, leftChildCopy);
        if (!leftChildCopy) {
            freeAST(leftChildCopy);
            freeAST(newHead);
            return NULL;
        }
    }

    return newHead;
}

AST* duplicateRightSubtree(AST* head) {
    if (!head)
        return NULL;
    AST* newHead = createNode(head->id, head->token);

    if (head->childCount > 0 && head->children[1]) {
        AST* leftChildCopy = duplicateTree(head->children[1]);
        addChild(newHead, leftChildCopy);
    }

    return newHead;
}

AST* buildFromParseResult(pParseResult parseResult) {
    AST* head = createNode(parseResult->p->adaptor->getUniqueID(parseResult->p->adaptor,
                                                                parseResult->sr.tree),
                           (char*)parseResult->sr.tree->getText(parseResult->sr.tree)->chars);

    int childCount = parseResult->sr.tree->getChildCount(parseResult->sr.tree);

    for(int i = 0; i < childCount; i++) {
        setChildFromAntlrNode(head, parseResult->p->adaptor,
                              parseResult->sr.tree->getChild(parseResult->sr.tree, i));
    }

    return head;
}

void setChildFromAntlrNode(AST* parent, pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE node) {
    if (!node)
        return;
    AST* child = createNode(adaptor->getUniqueID(adaptor, node),
                            (char*)node->getText(node)->chars);
    addChild(parent, child);

    int childCount = node->getChildCount(node);
    for (int i = 0; i < childCount; i++) {
        pANTLR3_BASE_TREE child_node = node->getChild(node, i);
        setChildFromAntlrNode(child, adaptor, child_node);
    }
}

void writeNode(AST* node, int basicBlockIndex, FILE *file) {
    fprintf(file, "    cluster_%d_node%u [label=\"%s\"];\n", basicBlockIndex,
                                                             node->id, node->token);
}

void writeEdge(AST* parent, AST* child, int basicBlockIndex, FILE *file) {
    fprintf(file, "    cluster_%d_node%u -> cluster_%d_node%u;\n",
            basicBlockIndex, parent->id, basicBlockIndex, child->id);
}

void outputOpNode(AST* node, int basicBlockIndex, FILE *file) {
    if (node == NULL) return;

    //printf("VISITING :: %s\n", node->token);
    int childCount = node->childCount;

    writeNode(node, basicBlockIndex, file);
    for (int i = 0; i < childCount; i++) {
        AST* child = getChild(node, i);
        outputOpNode(child, basicBlockIndex, file);
    }
}

void outputOpEdge(AST* parent, int basicBlockIndex, FILE *file) {
    if(!parent)
        return;
    int childCount = parent->childCount;

    for (int i = 0; i < childCount; i++) {
        AST* child = getChild(parent, i);

        writeEdge(parent, child, basicBlockIndex, file);
        outputOpEdge(child, basicBlockIndex, file);
    }
}

void analyzeCutCondition(AST* head) {
    AST* condition = getChild(head, 0);
    AST* leftOperand = getChild(condition, 0);
    AST* valuePlaceQualifier = createNode(arc4random(), "__read");
    insertBetween(condition, leftOperand, valuePlaceQualifier);
    for (size_t i = 1; i < condition->childCount; i++) {
        AST* element = getChild(condition, i);
        AST* readQualifier = createNode(arc4random(), "__read");
        insertBetween(condition, element, readQualifier);
    }

}

void analyzeIf(AST* ifNode) {
    if (ifNode->childCount < 2)
        return;
    analyzeCutCondition(ifNode);
}

void analyzeLoop(AST* loopNode) {
    if (!loopNode)
        return;

    analyzeCutCondition(loopNode);
}

void analyzeRepeat(AST* repeatNode) {
    if (!repeatNode)
        return;
    analyzeCutCondition(repeatNode);
}

void analyzeAssign(AST* assignNode) {
    AST* lvalue = getChild(assignNode, 0);
    AST* rvalue = getChild(assignNode, 1);
    AST* vp = createNode(arc4random(), "__read");
    AST* read = createNode(arc4random(), "__read");

    insertBetween(assignNode, lvalue, vp);
    insertBetween(assignNode, rvalue, read);
}

void analyzeCall(AST* call) {
    if (strcmp(call->token, "CALL")) {
        return;
    }

    if(call->childCount > 1) {
        AST* list_expr = getChild(call, 1);
        for (size_t i = 0; i < list_expr->childCount; i++) {
            AST* listChild = getChild(list_expr, i);
            if (listChild != NULL) {
                AST* read = createNode(arc4random(), "__read");
                insertBetween(list_expr, listChild, read);
                analyzeCall(listChild);
            }
        }
    }
}

AST* analyzeOp (AST* node) {
    if(!node) //merge block or another service blocks
        return NULL;
    AST* head = NULL;
    if(!strcmp(node->token, "CALL")) {
        head = duplicateLeftSubtree(node);
        analyzeCall(head);
    }
    if(!strcmp(node->token, "IF")) {
        head = duplicateLeftSubtree(node);
        analyzeIf(head);
    }
    if(!strcmp(node->token, "ELSE")) {
        head = duplicateTree(node);
    }
    if(!strcmp(node->token, "LOOP")) {
        head = duplicateLeftSubtree(node);
        analyzeLoop(head);
    }
    if(!strcmp(node->token, "REPEAT")) {
        head = duplicateRightSubtree(node);
        analyzeRepeat(head);
    }
    if(!strcmp(node->token, "VAR_DEF")) {
        head = duplicateTree(node);
    }
    if(!strcmp(node->token, "=")) {
        head = duplicateTree(node);
        analyzeAssign(head);
    }
    return head;
}
