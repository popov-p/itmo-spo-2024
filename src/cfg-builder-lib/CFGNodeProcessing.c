#include "CFGNodeProcessing.h"

#define TOKEN_IS(node, str) (!strcmp((node->token), (str)))


int cfgWalkerLinkWithParent(CFG* cfg,
                            AST* current) {
  BB* bb = createBasicBlock(current, standard);
  addBasicBlock(cfg, bb);
  int currentBlockIndex = cfg->blockCount - 1;

  if (cfg->lastProcessedIndex != -1)
    addSuccessor(cfg->blocks[cfg->lastProcessedIndex], currentBlockIndex);

  cfg->lastProcessedIndex = currentBlockIndex;
  printf("CFG :: WLP :: %s\n", current->token);
  return currentBlockIndex;
}

void enteringIf(CFG* cfg,
                AST* node) {
  int ifBlockIndex = cfgWalkerLinkWithParent(cfg, node);
  BB* mergeBlock = createBasicBlock(NULL, merge);
  addBasicBlock(cfg, mergeBlock);

  int mergeBlockIndex = cfg->blockCount - 1;

  pushIfEntry(cfg->ifLevelStack, ifBlockIndex, -1, mergeBlockIndex);
  cfg->lastProcessedIndex = ifBlockIndex;
  printf("CFG :: WP :: ENTERING IF\n");
}

void enteringElse(CFG* cfg,
                  AST* node) {
  BB* bb = createBasicBlock(node, standard);
  addBasicBlock(cfg, bb);
  int elseBlockIndex = cfg->blockCount - 1;
  cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].elseBlockIndex = elseBlockIndex;

  if(cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
    addSuccessor(cfg->blocks[cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].mergeBlockIndex],
                 cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex);
  }
  cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected = 0;


  if (cfg->lastProcessedIndex != -1) {
    addSuccessor(cfg->blocks[cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].ifBlockIndex], elseBlockIndex);
  }
  addSuccessor(cfg->blocks[cfg->lastProcessedIndex], cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].mergeBlockIndex);
  cfg->lastProcessedIndex = elseBlockIndex;
  printf("CFG :: WP :: ENTERING ELSE\n");
}

void cfgWalkerProcessCallNode(CFG* cfg,
                              AST* node) {
  int callIndex = cfgWalkerLinkWithParent(cfg, node);
  cfg->lastProcessedIndex = callIndex;
  printf("CFG :: WP :: CALL %s\n", (char*)getChild(node, 0)->token);
}

void enteringLoop(CFG* cfg,
                  AST* node) {
  int loopBlockIndex = cfgWalkerLinkWithParent(cfg, node);
  cfg->lastProcessedIndex = loopBlockIndex;

  BB* exitBlock = createBasicBlock(NULL, loop_exit);
  addBasicBlock(cfg, exitBlock);
  int exitBlockIndex = cfg->blockCount - 1;
  addSuccessor(cfg->blocks[loopBlockIndex], exitBlockIndex);
  pushLoopEntry(cfg->loopLevelStack, exitBlockIndex, loopBlockIndex);
  printf("CFG :: WP :: ENTERING LOOP\n");
}

void cfgWalkerProcessBreakNode(CFG* cfg,
                               AST* node) {
  cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected = 1;
  printf("CFG :: WP :: BREAK\n");
}

void enteringRepeat(CFG* cfg,
                    AST* node) {

  int repeatBlockIndex = cfgWalkerLinkWithParent(cfg, node);

  BB* exitBlock = createBasicBlock(NULL, repeat_exit);
  addBasicBlock(cfg, exitBlock);
  int exitBlockIndex = cfg->blockCount - 1;

  pushLoopEntry(cfg->loopLevelStack, exitBlockIndex, repeatBlockIndex);
  printf("CFG :: WP :: ENTETING REPEAT\n");
}

void cfgWalkerProcessBlockNode(CFG* cfg,
                               AST* node) {
  for (int i = 0; i < node->childCount; ++i) {
    AST* statementNode = getChild(node, i);
    cfgWalker(cfg, statementNode);
  }
  printf("CFG :: WP :: BLOCK\n");
}

void cfgWalkerProcessVarDecNode(CFG* cfg,
                                AST* node) {
  int varDecIndex = cfgWalkerLinkWithParent(cfg, node);
  cfg->lastProcessedIndex = varDecIndex;

  cfgWalker(cfg, getChild(node, 2));

  cfg->lastProcessedIndex = varDecIndex;

  printf("CFG :: WP :: VAR_DEC\n");
}


void cfgWalkerProcessVarDefNode(CFG* cfg,
                                AST* node) {
  int varDefIndex = cfgWalkerLinkWithParent(cfg, node);
  cfgWalker(cfg, getChild(node, 2));
  cfg->lastProcessedIndex = varDefIndex;
  printf("CFG :: WP :: VAR_DEF\n");
}

void cfgWalkerProcessAssignment(CFG* cfg,
                                AST* node) {
  int assignmentIndex = cfgWalkerLinkWithParent(cfg, node);
  cfg->lastProcessedIndex = assignmentIndex;
}

void cfgWalker(CFG* cfg, AST* node)
{
  if (!node) return;

  if (isProcessed(cfg->processedNodes, node))
  {
    printf("CFG :: WIP :: %s\n", node->token);
    return;
  }

  addProcessed(cfg->processedNodes, node);

  if (TOKEN_IS(node, "IF"))
    enteringIf(cfg,
               node);

  if (TOKEN_IS(node, "ELSE"))
    enteringElse(cfg,
                 node);

  if (TOKEN_IS(node, "LOOP"))
    enteringLoop(cfg,
                 node);

  if (TOKEN_IS(node, "REPEAT"))
    enteringRepeat(cfg,
                   node);

  if (TOKEN_IS(node, "BLOCK"))
    cfgWalkerProcessBlockNode(cfg,
                              node);

  if (TOKEN_IS(node, "BREAK"))
    cfgWalkerProcessBreakNode(cfg,
                              node);

  if(!cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
    for (int i = 0; i < node->childCount; i++)
      cfgWalker(cfg, getChild(node, i));
  }

  if (TOKEN_IS(node, "CALL"))
    cfgWalkerProcessCallNode(cfg,
                             node);

  if (TOKEN_IS(node, "ASSIGNMENT"))
    cfgWalkerProcessAssignment(cfg,
                               node);

  if (TOKEN_IS(node, "VAR_DEC"))
    cfgWalkerProcessVarDecNode(cfg,
                               node);
  if (TOKEN_IS(node, "VAR_DEF"))
    cfgWalkerProcessVarDecNode(cfg,
                               node);

  if (TOKEN_IS(node, "LOOP")) {
    printf("CFG :: W :: EXITING LOOP\n");
    if(cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
      addSuccessor(cfg->blocks[cfg->lastProcessedIndex],
                   cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex);
      cfg->lastProcessedIndex = cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex;
    }
    else {
      addSuccessor(cfg->blocks[cfg->lastProcessedIndex],
                   cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].loopIndex);
      cfg->lastProcessedIndex = cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex;
    }
    popLoopEntry(cfg->loopLevelStack);
  }
  if (TOKEN_IS(node, "REPEAT")) {
    if(cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
      addSuccessor(cfg->blocks[cfg->lastProcessedIndex],
                   cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex);
      cfg->lastProcessedIndex = cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex;
    }
    else {
      addSuccessor(cfg->blocks[cfg->lastProcessedIndex],
                   cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].loopIndex);
      addSuccessor(cfg->blocks[cfg->lastProcessedIndex],
                   cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex);
      cfg->lastProcessedIndex = cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex;
    }
    popLoopEntry(cfg->loopLevelStack);
  }
  if (TOKEN_IS(node, "IF")) {
    if (node->childCount == 2) {
      if(cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
        cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected = 0; // break elimination

        addSuccessor(cfg->blocks[cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].ifBlockIndex],
                     cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].mergeBlockIndex);

        addSuccessor(cfg->blocks[cfg->lastProcessedIndex],
                     cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex);
        cfg->lastProcessedIndex = cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].mergeBlockIndex;
      }
      else {
        addSuccessor(cfg->blocks[cfg->lastProcessedIndex],
                     cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].mergeBlockIndex);
        addSuccessor(cfg->blocks[cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].ifBlockIndex],
                     cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].mergeBlockIndex);

        cfg->lastProcessedIndex = cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].mergeBlockIndex;
      }
    }
    if(node->childCount == 3) {
      if(cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
        cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected = 0;
        addSuccessor(cfg->blocks[cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].mergeBlockIndex],
                     cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex);
      }
      printf("CFG :: W :: EXITING IF TO ELSE\n");
    }

    printf("CFG :: W :: EXITING IF\n");
    popIfEntry(cfg->ifLevelStack);
  }
  if (TOKEN_IS(node, "ELSE")) {
    if(cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected) {
      cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].breakDetected = 0;


      addSuccessor(cfg->blocks[cfg->lastProcessedIndex],
                   cfg->loopLevelStack->entries[cfg->loopLevelStack->currentLevel].exitBlockIndex);
      cfg->lastProcessedIndex = cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].mergeBlockIndex;
    }
    else {
      addSuccessor(cfg->blocks[cfg->lastProcessedIndex],
                   cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].mergeBlockIndex);
      cfg->lastProcessedIndex = cfg->ifLevelStack->entries[cfg->ifLevelStack->currentLevel].mergeBlockIndex;
    }
    printf("CFG :: W :: EXITING ELSE\n");
  }
}
