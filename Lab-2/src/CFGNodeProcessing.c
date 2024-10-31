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
    printf("CFG :: WLP :: %s\n", current->token);
    return currentBlockIndex;
}

void enteringIf(CFG* cfg,
                AST* node,
                int* lastBlockIndex) {
    int ifBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    pushIfEntry(cfg->ifLevelStack, ifBlockIndex);
}


void cfgWalkerProcessCallNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex) {
    int callIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = callIndex;
    printf("CFG :: WP :: CALL %s\n", (char*)getChild(node, 0)->token);
}

void enteringLoop(CFG* cfg,
                 AST* node,
                 int* lastBlockIndex) {
    int loopBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = loopBlockIndex;

    BasicBlock* exitBlock = createBasicBlock(NULL, loop_exit);
    addBasicBlock(cfg, exitBlock);
    int exitBlockIndex = cfg->blockCount - 1;
    addSuccessor(cfg->blocks[loopBlockIndex], exitBlockIndex);
    pushLoopEntry(cfg->loopLevelStack, exitBlockIndex, loopBlockIndex);
    printf("CFG :: WP :: ENTERING LOOP\n");
}

void cfgWalkerProcessBreakNode(CFG* cfg,
                               AST* node,
                               int* lastBlockIndex) {
    cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected = 1;
    printf("CFG :: WP :: BREAK\n");
}

void cfgWalkerProcessRepeatNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex) {
    cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    printf("CFG :: WP :: REPEAT\n");
}

void cfgWalkerProcessBlockNode(CFG* cfg,
                               AST* node,
                               int* lastBlockIndex) {
    for (int i = 0; i < node->childCount; ++i) {
        AST* statementNode = getChild(node, i);
        cfgWalker(cfg, statementNode, lastBlockIndex);
    }
    printf("CFG :: WP :: BLOCK\n");
}

void cfgWalkerProcessVarDecNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex) {
    int varDecIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = varDecIndex;

    cfgWalker(cfg, getChild(node, 2), lastBlockIndex);

    *lastBlockIndex = varDecIndex;

    printf("CFG :: WP :: VAR_DEC\n");
}


void cfgWalkerProcessVarDefNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex) {
    int varDefIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    cfgWalker(cfg, getChild(node, 2), lastBlockIndex);
    *lastBlockIndex = varDefIndex;
    printf("CFG :: WP :: VAR_DEF\n");
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
        printf("CFG :: WIP :: %s\n", node->token);
        return;
    }

    addProcessed(cfg->processedNodes, node);
    //printf("CFG :: W :: %s\n", (char*)node->token);

    int breakDetected = 0;
    if (!strcmp(node->token, "IF"))
        enteringIf(cfg,
                   node,
                   lastBlockIndex);
    if (!strcmp(node->token, "LOOP"))
        enteringLoop(cfg,
                    node,
                    lastBlockIndex);
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
    if (!strcmp(node->token, "BREAK"))
        cfgWalkerProcessBreakNode(cfg,
                                   node,
                                   lastBlockIndex);
    if(!cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
        for (int i = 0; i < node->childCount; i++)
            cfgWalker(cfg, getChild(node, i), lastBlockIndex);
    }
    if (!strcmp(node->token, "CALL"))
        cfgWalkerProcessCallNode(cfg,
                                 node,
                                 lastBlockIndex);
    if (strcmp(node->token, "=") == 0)
        cfgWalkerProcessAssignment(cfg,
                                   node,
                                   lastBlockIndex);

    if (!strcmp(node->token, "LOOP")) {
        printf("CFG :: W :: EXITING LOOP\n");
        if(cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
            addSuccessor(cfg->blocks[*lastBlockIndex],
                         cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex);
            *lastBlockIndex = cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex;
        }
        else {
            addSuccessor(cfg->blocks[*lastBlockIndex],
                         cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].loopIndex);
            //addSuccessor(cfg->blocks[*lastBlockIndex],
            //             cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex);
            *lastBlockIndex = cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex;
        }
        popLoopEntry(cfg->loopLevelStack);
    }
    if (!strcmp(node->token, "IF")) {
        BasicBlock* mergeBlock = createBasicBlock(NULL, merge);
        addBasicBlock(cfg, mergeBlock);
        int mergeBlockIndex = cfg->blockCount - 1;

        if (node->childCount == 2) {
            if(cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
                cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected = 0; // break elimination

                addSuccessor(cfg->blocks[cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].ifBlockIndex], mergeBlockIndex);
                addSuccessor(cfg->blocks[*lastBlockIndex],
                             cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex);
                *lastBlockIndex = mergeBlockIndex;
            }
            else {
                addSuccessor(cfg->blocks[*lastBlockIndex], mergeBlockIndex);
                addSuccessor(cfg->blocks[cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].ifBlockIndex], mergeBlockIndex);
                *lastBlockIndex = mergeBlockIndex;
            }
        }
        printf("CFG :: W :: EXITING IF\n");

        popIfEntry(cfg->ifLevelStack);
    }
}
