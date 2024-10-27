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
    return currentBlockIndex;
}

void cfgWalkerProcessIfNode(CFG* cfg,
                            AST* node,
                            int* lastBlockIndex,
                            int* childCount)
{
    int currentBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);

    BasicBlock* mergeBlock = createBasicBlock(NULL, merge);
    addBasicBlock(cfg, mergeBlock);
    int mergeBlockIndex = cfg->block_count - 1;

    int trueBranchIndex = currentBlockIndex;
    cfgWalker(cfg, getChild(node, 1), &trueBranchIndex);

    int falseBranchIndex = -1;
    if (*childCount > 2) {
        falseBranchIndex = currentBlockIndex;
        cfgWalker(cfg, getChild(node, 2), &falseBranchIndex);
    } else {
        addSuccessor(cfg->blocks[currentBlockIndex], mergeBlockIndex);
    }

    if (trueBranchIndex != -1) {
        addSuccessor(cfg->blocks[trueBranchIndex], mergeBlockIndex);
    }

    if (falseBranchIndex != -1) {
        addSuccessor(cfg->blocks[falseBranchIndex], mergeBlockIndex);
    }

    *lastBlockIndex = mergeBlockIndex;

    printf("Debug :: BB :: found IF block\n");
}

void cfgWalkerProcessCallNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex,
                              int* childCount)
{
    int currentBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = currentBlockIndex;
    char* func_name = getChild(node, 0)->token;
    printf("Debug :: BB :: found CALL: %s\n", func_name);
}















int isBreakStatement(AST* node) {
    return (strcmp(node->token, "BREAK") == 0);
}

int hasBreakStatementInBody(AST* loopNode) {
    for (int i = 0; i < loopNode->child_count; ++i) {
        AST* child = getChild(loopNode, i);
        if (isBreakStatement(child)) {
            return 1;
        }
    }
    return 0;
}

void cfgWalkerProcessLoopNode(CFG* cfg,
                              AST* node,
                              int* lastBlockIndex,
                              int* childCount) {
    enterLoop(cfg->loopLevelCounter);
    int hasBreak = 0;
    int loopBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = loopBlockIndex;

    int bodyBlockIndex = loopBlockIndex;
    for (int i = 1; i < node->child_count; ++i) {
        AST* child = getChild(node, i);
        if (isBreakStatement(child)) {
            hasBreak = 1;
        }
        cfgWalker(cfg, child, &bodyBlockIndex);
    }

    BasicBlock* exitBlock = createBasicBlock(NULL, loop_exit);
    addBasicBlock(cfg, exitBlock);
    int exitBlockIndex = cfg->block_count - 1;

    if (*lastBlockIndex != -1 && !hasBreak) {
        addSuccessor(cfg->blocks[*lastBlockIndex], exitBlockIndex);
    }

    if (!hasBreak) {
        addSuccessor(cfg->blocks[bodyBlockIndex], loopBlockIndex);
    }
    else {
        addSuccessor(cfg->blocks[bodyBlockIndex], exitBlockIndex);
    }

    *lastBlockIndex = exitBlockIndex;

    printf("Debug :: BB :: found LOOP block\n");
    exitLoop(cfg->loopLevelCounter);
}


void cfgWalkerProcessBreakNode(CFG* cfg,
                               AST* node,
                               int* lastBlockIndex,
                               int* childCount)
{
    int currentBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = currentBlockIndex;
    printf("Debug :: BB :: found BREAK statement\n");
}


void cfgWalkerProcessRepeatNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex,
                                int* childCount) {

    enterLoop(cfg->loopLevelCounter);
    int hasBreak = 0;
    int repeatBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = repeatBlockIndex;

    int bodyBlockIndex = repeatBlockIndex;

    AST* blockNode = getChild(node, 0);
    for (int i = 0; i < blockNode->child_count; ++i) {
        AST* child = getChild(blockNode, i);
        if (isBreakStatement(child)) {
            hasBreak = 1;
        }
        cfgWalker(cfg, child, &bodyBlockIndex);
    }


    BasicBlock* exitBlock = createBasicBlock(NULL, repeat_exit);
    addBasicBlock(cfg, exitBlock);
    int exitBlockIndex = cfg->block_count - 1;

    if (*lastBlockIndex != -1 && !hasBreak) {
        addSuccessor(cfg->blocks[*lastBlockIndex], exitBlockIndex);
    }

    if (!hasBreak) {
        addSuccessor(cfg->blocks[bodyBlockIndex], repeatBlockIndex);
    }
    else {
        addSuccessor(cfg->blocks[bodyBlockIndex], exitBlockIndex);
    }


    *lastBlockIndex = exitBlockIndex;

    printf("Debug :: BB :: found REPEAT block\n");
    exitLoop(cfg->loopLevelCounter);
}


void cfgWalkerProcessBlockNode(CFG* cfg,
                               AST* node,
                               int* lastBlockIndex,
                               int* childCount) {
    int numStatements = node->child_count;

    for (int i = 0; i < numStatements; ++i) {
        AST* statementNode = getChild(node, i);
        cfgWalker(cfg, statementNode, lastBlockIndex);
    }

    printf("Debug :: BB :: found BLOCK block\n");
}



void cfgWalkerProcessVarDecNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex,
                                int* childCount)
{
    int currentBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);
    *lastBlockIndex = currentBlockIndex;

    cfgWalker(cfg, getChild(node, 2), lastBlockIndex);

    *lastBlockIndex = currentBlockIndex;

    printf("Debug :: BB :: found VAR_DEC block'\n");
}


void cfgWalkerProcessVarDefNode(CFG* cfg,
                                AST* node,
                                int* lastBlockIndex,
                                int* childCount) {
    int currentBlockIndex = cfgWalkerLinkWithParent(cfg, node, lastBlockIndex);

    *lastBlockIndex = currentBlockIndex;

    cfgWalker(cfg, getChild(node, 2), lastBlockIndex);

    *lastBlockIndex = currentBlockIndex;

    printf("Debug :: BB :: found VAR_DEF block for variable\n");
}


void cfgWalker(CFG* cfg, AST* node, int* lastBlockIndex)
{
    if (node == NULL) return;

    if (isProcessed(cfg->processedNodes, node))
    {
        printf("Debug :: BB :: Already processed node: %s\n", node->token);
        return;
    }

    addProcessed(cfg->processedNodes, node);

    char* name = node->token;
    int childCount = node->child_count;
    printf("Debug :: BB :: Visiting node: %s\n", (char*)name);

    if (strcmp(name, "IF") == 0)
        cfgWalkerProcessIfNode(cfg,
                               node,
                               lastBlockIndex,
                               &childCount);
    else if (strcmp(name, "LOOP") == 0)
        cfgWalkerProcessLoopNode(cfg,
                                 node,
                                 lastBlockIndex,
                                 &childCount);
    else if (strcmp(name, "REPEAT") == 0)
        cfgWalkerProcessRepeatNode(cfg,
                                 node,
                                 lastBlockIndex,
                                 &childCount);
    else if (strcmp(name, "BLOCK") == 0)
        cfgWalkerProcessBlockNode(cfg,
                                   node,
                                   lastBlockIndex,
                                   &childCount);
    else if (strcmp(name, "VAR_DEC") == 0)
        cfgWalkerProcessVarDecNode(cfg,
                                   node,
                                   lastBlockIndex,
                                   &childCount);
    else if (strcmp(name, "VAR_DEF") == 0)
        cfgWalkerProcessVarDecNode(cfg,
                                   node,
                                   lastBlockIndex,
                                   &childCount);
    else if (strcmp(name, "BREAK") == 0)
        cfgWalkerProcessBreakNode(cfg,
                                   node,
                                   lastBlockIndex,
                                   &childCount);
    else if (strcmp(name, "=") == 0) {
        if (*lastBlockIndex != -1) {
            BasicBlock* assignBlock = createBasicBlock(node, standard);
            addBasicBlock(cfg, assignBlock);
            int currentBlockIndex = cfg->block_count - 1;
            addSuccessor(cfg->blocks[*lastBlockIndex], currentBlockIndex);
            *lastBlockIndex = currentBlockIndex;

            char* lhs = getChild(node, 0)->token;
            char* rhs = getChild(node, 1)->token;
            printf("BB :: found assignment: %s = %s\n", lhs, rhs);
        }
    }

    for (int i = 0; i < childCount; i++) {
        AST* child = getChild(node, i);
        cfgWalker(cfg, child, lastBlockIndex);
    }

    if (strcmp(node->token, "CALL") == 0)
        cfgWalkerProcessCallNode(cfg,
                                 node,
                                 lastBlockIndex,
                                 &childCount);
}
