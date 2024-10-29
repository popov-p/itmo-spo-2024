#include "CFGNodeProcessing.h"

int cfgWalkerLinkWithParent(CFG* cfg,
                            AST* current,
                            int* lastBlockIndex) {
    BasicBlock* bb = createBasicBlock(current, standard);
    addBasicBlock(cfg, bb);
    int currentBlockIndex = cfg->block_count - 1;

    if (*lastBlockIndex != -1) {
        addSuccessor(cfg->blocks[*lastBlockIndex], currentBlockIndex);
    }

    *lastBlockIndex = currentBlockIndex;
    printf("WLP :: %s\n", current->token);
    return currentBlockIndex;
}

void cfgWalkerProcessIfNode(CFG* cfg,
                            AST* node,
                            int* lastBlockIndex,
                            int* breakDetected) {
    int ifBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);

    BasicBlock* mergeBlock = createBasicBlock(NULL, merge);
    addBasicBlock(cfg, mergeBlock);
    int mergeBlockIndex = cfg->block_count - 1;

    int ifBlockIter = ifBlockIndex;
    if (node->child_count > 1) {
        cfgWalker(cfg, getChild(node, 1), &ifBlockIter);
        addSuccessor(cfg->blocks[ifBlockIter], mergeBlockIndex);
        if (node->child_count == 2) {
            addSuccessor(cfg->blocks[ifBlockIndex], mergeBlockIndex);
        }
        if(cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
            addSuccessor(cfg->blocks[mergeBlockIndex], getCurrentLoopEntry(cfg->loopLevelStack).loopIndex);
            //addSuccessor(cfg->blocks[ifBlockIndex], getCurrentLoopEntry(cfg->loopLevelStack).exitBlockIndex);
            //addSuccessor(cfg->blocks[mergeBlockIndex], getCurrentLoopEntry(cfg->loopLevelStack).loopIndex);
        }
    }

    if (node->child_count > 2) {
        int elseBlockIter = ifBlockIndex;
        cfgWalker(cfg, getChild(node, 2), &elseBlockIter);
        addSuccessor(cfg->blocks[elseBlockIter], mergeBlockIndex);
    }
    *lastBlockIndex = mergeBlockIndex;
}


void cfgWalkerProcessCallNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex)
{
    int callIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = callIndex;
    printf("WP :: CALL %s\n", (char*)getChild(node, 0)->token);
}

void cfgWalkerProcessLoopNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex,
                              int* breakDetected) {
    int loopBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    int loopBlockIter = loopBlockIndex;
    *lastBlockIndex = loopBlockIndex;

    BasicBlock* exitBlock = createBasicBlock(NULL, loop_exit);
    addBasicBlock(cfg, exitBlock);
    int exitBlockIndex = cfg->block_count - 1;
    pushLoopEntry(cfg->loopLevelStack, exitBlockIndex, loopBlockIndex);

    for (int i = 1; i < node->child_count; ++i) {
        AST* child = getChild(node, i);
        cfgWalker(cfg, child, &loopBlockIter);
        if (getCurrentLoopEntry(cfg->loopLevelStack).breakDetected) {
            *breakDetected = 1; // запрещаем обработку дальнейших нод
            break;
        }
    }
    if(!(cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected)) {
        addSuccessor(cfg->blocks[loopBlockIter], loopBlockIndex);
        addSuccessor(cfg->blocks[loopBlockIndex], exitBlockIndex);
    }
    else
    {
        addSuccessor(cfg->blocks[loopBlockIter], exitBlockIndex);
    }

    *lastBlockIndex = exitBlockIndex;

    popLoopEntry(cfg->loopLevelStack);
    printf("WP :: LOOP \n");
}


void cfgWalkerProcessBreakNode(CFG* cfg,
                               AST* node,
                               int* lastBlockIndex)
{
    cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected = 1;
    int breakIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = breakIndex;
    printf("WP :: BREAK\n");
}


void cfgWalkerProcessRepeatNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex) {
    int repeatBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    printf("WP :: REPEAT\n");
}


void cfgWalkerProcessBlockNode(CFG* cfg,
                               AST* node,
                               int* lastBlockIndex) {
    int numStatements = node->child_count;

    for (int i = 0; i < numStatements; ++i) {
        AST* statementNode = getChild(node, i);
        cfgWalker(cfg, statementNode, lastBlockIndex);
    }

    printf("WP :: BLOCK\n");
}

void cfgWalkerProcessVarDecNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex)
{
    int currentBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = currentBlockIndex;

    cfgWalker(cfg, getChild(node, 2), lastBlockIndex);

    *lastBlockIndex = currentBlockIndex;

    printf("WP :: VAR_DEC\n");
}


void cfgWalkerProcessVarDefNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex) {
    int varDefIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    cfgWalker(cfg, getChild(node, 2), lastBlockIndex);
    *lastBlockIndex = varDefIndex;
    printf("WP :: VAR_DEF\n");
}

void cfgWalkerProcessAssignment(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex) {
    int currentBlockIndex = cfgWalkerLinkWithParent(cfg,node,lastBlockIndex);
    *lastBlockIndex = currentBlockIndex;
}

void cfgWalker(CFG* cfg, AST* node, int* lastBlockIndex)
{
    if (node == NULL) return;

    if (isProcessed(cfg->processedNodes, node))
    {
        printf("WAP :: %s\n", node->token);
        return;
    }

    addProcessed(cfg->processedNodes, node);
    printf("W :: %s\n", (char*)node->token);

    int breakDetected = 0;

    if (strcmp(node->token, "IF") == 0) {
        cfgWalkerProcessIfNode(cfg,
                               node,
                               lastBlockIndex,
                               &breakDetected);
        if (breakDetected) return;
    }
    else if (strcmp(node->token, "LOOP") == 0) {
        cfgWalkerProcessLoopNode(cfg,
                                 node,
                                 lastBlockIndex,
                                 &breakDetected);
    }
    else if (strcmp(node->token, "REPEAT") == 0)
        cfgWalkerProcessRepeatNode(cfg,
                                 node,
                                 lastBlockIndex);
    else if (strcmp(node->token, "BLOCK") == 0)
        cfgWalkerProcessBlockNode(cfg,
                                   node,
                                   lastBlockIndex);
    else if (strcmp(node->token, "VAR_DEC") == 0)
        cfgWalkerProcessVarDecNode(cfg,
                                   node,
                                   lastBlockIndex);
    else if (strcmp(node->token, "VAR_DEF") == 0)
        cfgWalkerProcessVarDecNode(cfg,
                                   node,
                                   lastBlockIndex);
    else if (strcmp(node->token, "BREAK") == 0)
        cfgWalkerProcessBreakNode(cfg,
                                   node,
                                   lastBlockIndex);

    for (int i = 0; i < node->child_count; i++) {
        AST* child = getChild(node, i);
        cfgWalker(cfg, child, lastBlockIndex);
    }

    if (strcmp(node->token, "CALL") == 0)
        cfgWalkerProcessCallNode(cfg,
                                 node,
                                 lastBlockIndex);
    else if (strcmp(node->token, "=") == 0) {
        cfgWalkerProcessAssignment(cfg,
                                   node,
                                   lastBlockIndex);
    }
}
