#include "CFGNodeProcessing.h"

int cfgWalkerLinkWithParent(CFG* cfg,
                            AST* current,
                            int* lastBlockIndex) {
    BasicBlock* bb = createBasicBlock(current, standard);
    addBasicBlock(cfg, bb);
    int currentBlockIndex = cfg->blockCount - 1;

    if (*lastBlockIndex != -1) {
        addSuccessor(cfg->blocks[*lastBlockIndex], currentBlockIndex);
    }

    *lastBlockIndex = currentBlockIndex;
    printf("WLP :: %s\n", current->token);
    return currentBlockIndex;
}

void cfgWalkerProcessIfNode(CFG* cfg,
                            AST* node,
                            int* lastBlockIndex) {
    int ifBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    BasicBlock* mergeBlock = createBasicBlock(NULL, merge);
    addBasicBlock(cfg, mergeBlock);
    int mergeBlockIndex = cfg->blockCount - 1;
    if (node->childCount == 2) {
        int ifBlockIter = ifBlockIndex;
        cfgWalker(cfg, getChild(node, 1), &ifBlockIter);
        if(cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
            /*todo*/
            *lastBlockIndex = mergeBlockIndex;
        }
        else {
            addSuccessor(cfg->blocks[ifBlockIter], mergeBlockIndex);
            addSuccessor(cfg->blocks[ifBlockIndex], mergeBlockIndex);
            *lastBlockIndex = mergeBlockIndex;
        }
    }
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
    int exitBlockIndex = cfg->blockCount - 1;
    pushLoopEntry(cfg->loopLevelStack, exitBlockIndex, loopBlockIndex);

    for (int i = 1; i < node->childCount; ++i) {
        AST* child = getChild(node, i);
        cfgWalker(cfg, child, &loopBlockIter);
        if (getCurrentLoopEntry(cfg->loopLevelStack).breakDetected) {
            *breakDetected = 1;
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
    printf("WP :: LOOP\n");
}


void cfgWalkerProcessBreakNode(CFG* cfg,
                               AST* node,
                               int* lastBlockIndex,
                               int* breakDetected)
{
    *breakDetected = 1;
    cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected = 1;
    int breakIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = breakIndex;
    printf("WP :: BREAK\n");
}


void cfgWalkerProcessRepeatNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex) {
    cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    printf("WP :: REPEAT\n");
}


void cfgWalkerProcessBlockNode(CFG* cfg,
                               AST* node,
                               int* lastBlockIndex) {
    for (int i = 0; i < node->childCount; ++i) {
        AST* statementNode = getChild(node, i);
        cfgWalker(cfg, statementNode, lastBlockIndex);
    }
    printf("WP :: BLOCK\n");
}

void cfgWalkerProcessVarDecNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex)
{
    int varDecIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = varDecIndex;

    cfgWalker(cfg, getChild(node, 2), lastBlockIndex);

    *lastBlockIndex = varDecIndex;

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
    int assignmentIndex = cfgWalkerLinkWithParent(cfg,node,lastBlockIndex);
    *lastBlockIndex = assignmentIndex;
}

void cfgWalker(CFG* cfg, AST* node, int* lastBlockIndex)
{
    if (node == NULL) return;

    if (isProcessed(cfg->processedNodes, node))
    {
        printf("WIP :: %s\n", node->token);
        return;
    }

    addProcessed(cfg->processedNodes, node);
    printf("W :: %s\n", (char*)node->token);

    int breakDetected = 0;
    if (!strcmp(node->token, "IF")) {
        cfgWalkerProcessIfNode(cfg,
                               node,
                               lastBlockIndex);
    }
    if (!strcmp(node->token, "LOOP")) {
        cfgWalkerProcessLoopNode(cfg,
                                 node,
                                 lastBlockIndex, &breakDetected);
        // if(breakDetected) return;
    }
    if (!strcmp(node->token, "REPEAT"))
        cfgWalkerProcessRepeatNode(cfg,
                                 node,
                                 lastBlockIndex);
    if (!strcmp(node->token, "BLOCK"))
        cfgWalkerProcessBlockNode(cfg,
                                   node,
                                   lastBlockIndex);
    if (!strcmp(node->token, "VAR_DEC"))
        cfgWalkerProcessVarDecNode(cfg,
                                   node,
                                   lastBlockIndex);
    if (!strcmp(node->token, "VAR_DEF"))
        cfgWalkerProcessVarDecNode(cfg,
                                   node,
                                   lastBlockIndex);
    if (!strcmp(node->token, "BREAK")) {
        cfgWalkerProcessBreakNode(cfg,
                                   node,
                                   lastBlockIndex,
                                   &breakDetected);
    }

    if (!cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
        for (int i = 0; i < node->childCount; i++) {
            cfgWalker(cfg, getChild(node, i), lastBlockIndex);
        }
    }

    if (!strcmp(node->token, "CALL")) {
        cfgWalkerProcessCallNode(cfg,
                                 node,
                                 lastBlockIndex);
    }
    if (strcmp(node->token, "=") == 0) {
        cfgWalkerProcessAssignment(cfg,
                                   node,
                                   lastBlockIndex);
    }
}
