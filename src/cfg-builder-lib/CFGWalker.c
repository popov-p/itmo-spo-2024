#include "CFGWalker.h"

#define TOKEN_IS(node, str) (!strcmp((node->token), (str)))
#define BREAK_DETECTED(cfg) ((cfg)->loopLevelStack->entries[(cfg)->loopLevelStack->currentLevel].breakDetected)
#define LAST_MERGE_IDX(cfg) ((cfg)->ifLevelStack->entries[(cfg)->ifLevelStack->currentLevel].mergeBlockIndex)
#define LAST_IF_IDX(cfg) ((cfg)->ifLevelStack->entries[(cfg)->ifLevelStack->currentLevel].ifBlockIndex)
#define LAST_LOOP_EXIT_IDX(cfg) ((cfg)->loopLevelStack->entries[(cfg)->loopLevelStack->currentLevel].exitBlockIndex)
#define LAST_LOOP_IDX(cfg) ((cfg)->loopLevelStack->entries[(cfg)->loopLevelStack->currentLevel].loopIndex)
#define LAST_PROCESSED_BLOCK(cfg) ((cfg)->blocks[(cfg)->lastProcessedIndex])
#define LAST_ELSE_IDX(cfg) ((cfg)->ifLevelStack->entries[(cfg)->ifLevelStack->currentLevel].elseBlockIndex)

int connectNewBlock(CFG* cfg,
                    AST* current) {
  BB* bb = createBasicBlock(current, standard);
  addBasicBlock(cfg, bb);
  int currentBlockIndex = cfg->blockCount - 1;

  if (cfg->lastProcessedIndex != -1)
    addSuccessor(LAST_PROCESSED_BLOCK(cfg), currentBlockIndex);

  cfg->lastProcessedIndex = currentBlockIndex;
  printf("CFG :: CONNECT NEW BLOCK :: %s\n", current->token);
  return currentBlockIndex;
}

void enterIf(CFG* cfg,
             AST* node) {
  int ifBlockIndex = connectNewBlock(cfg, node);
  BB* mergeBlock = createBasicBlock(NULL, merge);
  addBasicBlock(cfg, mergeBlock);

  int mergeBlockIndex = cfg->blockCount - 1;

  pushIfEntry(cfg->ifLevelStack, ifBlockIndex, -1, mergeBlockIndex);
  cfg->lastProcessedIndex = ifBlockIndex;
  printf("CFG :: ENTERING IF\n");
}
void exitIf(CFG* cfg,
            AST* node)  {
  if (node->childCount == 2) {
    if(BREAK_DETECTED(cfg)) {
      BREAK_DETECTED(cfg) = 0;

      addSuccessor(cfg->blocks[LAST_IF_IDX(cfg)],
                   LAST_MERGE_IDX(cfg));

      addSuccessor(LAST_PROCESSED_BLOCK(cfg),
                   LAST_LOOP_EXIT_IDX(cfg));
      cfg->lastProcessedIndex = LAST_MERGE_IDX(cfg);
    }
    else {
      addSuccessor(LAST_PROCESSED_BLOCK(cfg),
                   LAST_MERGE_IDX(cfg));
      addSuccessor(cfg->blocks[LAST_IF_IDX(cfg)],
                   LAST_MERGE_IDX(cfg));

      cfg->lastProcessedIndex = LAST_MERGE_IDX(cfg);
    }
  }
  if(node->childCount == 3) {
    if(BREAK_DETECTED(cfg)) {
      BREAK_DETECTED(cfg) = 0;
      addSuccessor(cfg->blocks[LAST_MERGE_IDX(cfg)],
                   LAST_LOOP_EXIT_IDX(cfg));
    }
    printf("CFG :: EXITING IF TO ELSE\n");
  }

  printf("CFG :: EXITING IF\n");
  popIfEntry(cfg->ifLevelStack);
}


void enterElse(CFG* cfg,
               AST* node) {
  BB* bb = createBasicBlock(node, standard);
  addBasicBlock(cfg, bb);
  int elseBlockIndex = cfg->blockCount - 1;
  LAST_ELSE_IDX(cfg) = elseBlockIndex;

  if(BREAK_DETECTED(cfg))
    addSuccessor(cfg->blocks[LAST_MERGE_IDX(cfg)],
                 LAST_LOOP_EXIT_IDX(cfg));

  BREAK_DETECTED(cfg) = 0;

  if (cfg->lastProcessedIndex != -1) {
    addSuccessor(cfg->blocks[LAST_IF_IDX(cfg)], elseBlockIndex);
  }
  addSuccessor(LAST_PROCESSED_BLOCK(cfg), LAST_MERGE_IDX(cfg));
  cfg->lastProcessedIndex = elseBlockIndex;
  printf("CFG :: ENTERING ELSE\n");
}

void exitElse(CFG* cfg, AST* node) {
  if(BREAK_DETECTED(cfg)) {
    BREAK_DETECTED(cfg) = 0;

    addSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_EXIT_IDX(cfg));
    cfg->lastProcessedIndex = LAST_MERGE_IDX(cfg);
  }
  else {
    addSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_MERGE_IDX(cfg));
    cfg->lastProcessedIndex = LAST_MERGE_IDX(cfg);
  }
  printf("CFG :: EXITING ELSE\n");
}


void exitCall(CFG* cfg, AST* node) {
  int callIndex = connectNewBlock(cfg, node);
  cfg->lastProcessedIndex = callIndex;
  printf("CFG :: CALL %s\n", (char*)getChild(node, 0)->token);
}

void enterLoop(CFG* cfg,
                  AST* node) {
  int loopBlockIndex = connectNewBlock(cfg, node);
  cfg->lastProcessedIndex = loopBlockIndex;

  BB* exitBlock = createBasicBlock(NULL, loop_exit);
  addBasicBlock(cfg, exitBlock);
  int exitBlockIndex = cfg->blockCount - 1;
  addSuccessor(cfg->blocks[loopBlockIndex], exitBlockIndex);
  pushLoopEntry(cfg->loopLevelStack, exitBlockIndex, loopBlockIndex);
  printf("CFG :: ENTERING LOOP\n");
}

void exitLoop(CFG* cfg,
              AST* node) {
  printf("CFG :: EXITING LOOP\n");
  if(BREAK_DETECTED(cfg)) {
    addSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_EXIT_IDX(cfg));
    cfg->lastProcessedIndex = LAST_LOOP_EXIT_IDX(cfg);
  }
  else {
    addSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_IDX(cfg));
    cfg->lastProcessedIndex = LAST_LOOP_EXIT_IDX(cfg);
  }
  popLoopEntry(cfg->loopLevelStack);
}

void enterBreak(CFG* cfg, AST* node) {
  BREAK_DETECTED(cfg) = 1;
  printf("CFG :: BREAK\n");
}

void enterRepeat(CFG* cfg,
                 AST* node) {

  int repeatBlockIndex = connectNewBlock(cfg, node);

  BB* exitBlock = createBasicBlock(NULL, repeat_exit);
  addBasicBlock(cfg, exitBlock);
  int exitBlockIndex = cfg->blockCount - 1;

  pushLoopEntry(cfg->loopLevelStack, exitBlockIndex, repeatBlockIndex);
  printf("CFG :: ENTER REPEAT\n");
}
void exitRepeat(CFG* cfg,
                AST* node) {
  if(BREAK_DETECTED(cfg)) {
    addSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_EXIT_IDX(cfg));
    cfg->lastProcessedIndex = LAST_LOOP_EXIT_IDX(cfg);
  }
  else {
    addSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_IDX(cfg));
    addSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_EXIT_IDX(cfg));
    cfg->lastProcessedIndex = LAST_LOOP_EXIT_IDX(cfg);
  }
  popLoopEntry(cfg->loopLevelStack);
}

void enterVarDec(CFG* cfg,
                 AST* node) {
  int varDecIndex = connectNewBlock(cfg, node);
  cfg->lastProcessedIndex = varDecIndex;
  printf("CFG :: VAR_DEC\n");
}

void enterVarDef(CFG* cfg,
                 AST* node) {
  int varDefIndex = connectNewBlock(cfg, node);
  cfg->lastProcessedIndex = varDefIndex;
  printf("CFG :: VAR_DEF\n");
}

void enterAssignment(CFG* cfg,
                     AST* node) {
  int assignmentIndex = connectNewBlock(cfg, node);
  cfg->blocks[assignmentIndex]->opTree = otAssignment(node);
  cfg->lastProcessedIndex = assignmentIndex;
}

void cfgWalker(CFG* cfg, AST* node)
{
  if (!node) return;

  if (TOKEN_IS(node, "IF"))
    enterIf(cfg, node);

  if (TOKEN_IS(node, "ELSE"))
    enterElse(cfg, node);

  if (TOKEN_IS(node, "LOOP"))
    enterLoop(cfg, node);

  if (TOKEN_IS(node, "REPEAT"))
    enterRepeat(cfg, node);

  if (TOKEN_IS(node, "BREAK"))
    enterBreak(cfg, node);

  if (TOKEN_IS(node, "ASSIGNMENT"))
    enterAssignment(cfg,
                    node);

  if (TOKEN_IS(node, "VAR_DEC"))
    enterVarDec(cfg, node);

  if (TOKEN_IS(node, "VAR_DEF"))
    enterVarDec(cfg, node);

  if(!BREAK_DETECTED(cfg))
    for (int i = 0; i < node->childCount; i++)
      cfgWalker(cfg, getChild(node, i));

  if (TOKEN_IS(node, "CALL"))
    exitCall(cfg, node);

  if (TOKEN_IS(node, "LOOP"))
    exitLoop(cfg, node);

  if (TOKEN_IS(node, "REPEAT"))
    exitRepeat(cfg, node);

  if (TOKEN_IS(node, "IF"))
    exitIf(cfg, node);

  if (TOKEN_IS(node, "ELSE"))
    exitElse(cfg, node);
}
