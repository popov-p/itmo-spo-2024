#include "CFGWalker.h"

#define BREAK_DETECTED(cfg) ((cfg)->loopStack->entries[(cfg)->loopStack->currentLevel].breakDetected)
#define LAST_MERGE_IDX(cfg) ((cfg)->ifStack->entries[(cfg)->ifStack->currentLevel].mergeBlockIndex)
#define LAST_IF_IDX(cfg) ((cfg)->ifStack->entries[(cfg)->ifStack->currentLevel].ifBlockIndex)
#define LAST_LOOP_EXIT_IDX(cfg) ((cfg)->loopStack->entries[(cfg)->loopStack->currentLevel].exitBlockIndex)
#define LAST_LOOP_IDX(cfg) ((cfg)->loopStack->entries[(cfg)->loopStack->currentLevel].loopIndex)
#define LAST_ELSE_IDX(cfg) ((cfg)->ifStack->entries[(cfg)->ifStack->currentLevel].elseBlockIndex)
#define LAST_PROCESSED_BLOCK(cfg) ((cfg)->blocks[(cfg)->lastProcessedIndex])

int CFG_ConnectNewBlock(CFG* cfg,
                    AST* current) {
  BB* bb = CFG_CreateBB(current, standard);
  CFG_AddBB(cfg, bb);
  int currentBlockIndex = cfg->blockCount - 1;

  if (cfg->lastProcessedIndex != -1)
    CFG_AddSuccessor(LAST_PROCESSED_BLOCK(cfg), currentBlockIndex);

  cfg->lastProcessedIndex = currentBlockIndex;
  printf("CFG :: CONNECT NEW BLOCK :: %s\n", current->token);
  return currentBlockIndex;
}

void CFG_EnterIf(CFG* cfg,
             AST* node) {
  int ifBlockIndex = CFG_ConnectNewBlock(cfg, node);
  BB* mergeBlock = CFG_CreateBB(NULL, merge);
  CFG_AddBB(cfg, mergeBlock);

  int mergeBlockIndex = cfg->blockCount - 1;

  IS_PushIE(cfg->ifStack, ifBlockIndex, -1, mergeBlockIndex);
  cfg->lastProcessedIndex = ifBlockIndex;
  printf("CFG :: ENTERING AST_IF\n");
}
void CFG_ExitIf(CFG* cfg,
            AST* node)  {
  if (node->childCount == 2) {
    if(BREAK_DETECTED(cfg)) {
      BREAK_DETECTED(cfg) = 0;

      CFG_AddSuccessor(cfg->blocks[LAST_IF_IDX(cfg)],
                   LAST_MERGE_IDX(cfg));

      CFG_AddSuccessor(LAST_PROCESSED_BLOCK(cfg),
                   LAST_LOOP_EXIT_IDX(cfg));
      cfg->lastProcessedIndex = LAST_MERGE_IDX(cfg);
    }
    else {
      CFG_AddSuccessor(LAST_PROCESSED_BLOCK(cfg),
                   LAST_MERGE_IDX(cfg));
      CFG_AddSuccessor(cfg->blocks[LAST_IF_IDX(cfg)],
                   LAST_MERGE_IDX(cfg));

      cfg->lastProcessedIndex = LAST_MERGE_IDX(cfg);
    }
  }
  if(node->childCount == 3) {
    if(BREAK_DETECTED(cfg)) {
      BREAK_DETECTED(cfg) = 0;
      CFG_AddSuccessor(cfg->blocks[LAST_MERGE_IDX(cfg)],
                   LAST_LOOP_EXIT_IDX(cfg));
    }
    printf("CFG :: EXITING AST_IF TO AST_ELSE\n");
  }

  printf("CFG :: EXITING AST_IF\n");
  IS_PopIE(cfg->ifStack);
}


void CFG_EnterElse(CFG* cfg,
               AST* node) {
  BB* bb = CFG_CreateBB(node, standard);
  CFG_AddBB(cfg, bb);
  int elseBlockIndex = cfg->blockCount - 1;
  LAST_ELSE_IDX(cfg) = elseBlockIndex;

  if(BREAK_DETECTED(cfg))
    CFG_AddSuccessor(cfg->blocks[LAST_MERGE_IDX(cfg)],
                 LAST_LOOP_EXIT_IDX(cfg));

  BREAK_DETECTED(cfg) = 0;

  if (cfg->lastProcessedIndex != -1) {
    CFG_AddSuccessor(cfg->blocks[LAST_IF_IDX(cfg)], elseBlockIndex);
  }
  CFG_AddSuccessor(LAST_PROCESSED_BLOCK(cfg), LAST_MERGE_IDX(cfg));
  cfg->lastProcessedIndex = elseBlockIndex;
  printf("CFG :: ENTERING AST_ELSE\n");
}

void CFG_ExitElse(CFG* cfg, AST* node) {
  if(BREAK_DETECTED(cfg)) {
    BREAK_DETECTED(cfg) = 0;

    CFG_AddSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_EXIT_IDX(cfg));
    cfg->lastProcessedIndex = LAST_MERGE_IDX(cfg);
  }
  else {
    CFG_AddSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_MERGE_IDX(cfg));
    cfg->lastProcessedIndex = LAST_MERGE_IDX(cfg);
  }
  printf("CFG :: EXITING AST_ELSE\n");
}


void CFG_ExitCall(CFG* cfg, AST* node) {
  int callIndex = CFG_ConnectNewBlock(cfg, node);
  cfg->lastProcessedIndex = callIndex;
  printf("CFG :: AST_CALL %s\n", (char*)AST_GetChild(node, 0)->token);
}

void CFG_EnterLoop(CFG* cfg,
               AST* node) {
  int loopBlockIndex = CFG_ConnectNewBlock(cfg, node);
  cfg->lastProcessedIndex = loopBlockIndex;

  BB* exitBlock = CFG_CreateBB(NULL, loop_exit);
  CFG_AddBB(cfg, exitBlock);
  int exitBlockIndex = cfg->blockCount - 1;
  CFG_AddSuccessor(cfg->blocks[loopBlockIndex], exitBlockIndex);
  LS_PushLE(cfg->loopStack, exitBlockIndex, loopBlockIndex);
  printf("CFG :: ENTERING AST_LOOP\n");
}

void CFG_ExitLoop(CFG* cfg,
              AST* node) {
  printf("CFG :: EXITING AST_LOOP\n");
  if(BREAK_DETECTED(cfg)) {
    CFG_AddSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_EXIT_IDX(cfg));
    cfg->lastProcessedIndex = LAST_LOOP_EXIT_IDX(cfg);
  }
  else {
    CFG_AddSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_IDX(cfg));
    cfg->lastProcessedIndex = LAST_LOOP_EXIT_IDX(cfg);
  }
  LS_PopLE(cfg->loopStack);
}

void CFG_EnterBreak(CFG* cfg, AST* node) {
  BREAK_DETECTED(cfg) = 1;
  printf("CFG :: AST_BREAK\n");
}

void CFG_EnterRepeat(CFG* cfg,
                 AST* node) {

  int repeatBlockIndex = CFG_ConnectNewBlock(cfg, node);

  BB* exitBlock = CFG_CreateBB(NULL, repeat_exit);
  CFG_AddBB(cfg, exitBlock);
  int exitBlockIndex = cfg->blockCount - 1;

  LS_PushLE(cfg->loopStack, exitBlockIndex, repeatBlockIndex);
  printf("CFG :: ENTER AST_REPEAT\n");
}
void CFG_ExitRepeat(CFG* cfg,
                AST* node) {
  if(BREAK_DETECTED(cfg)) {
    CFG_AddSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_EXIT_IDX(cfg));
    cfg->lastProcessedIndex = LAST_LOOP_EXIT_IDX(cfg);
  }
  else {
    CFG_AddSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_IDX(cfg));
    CFG_AddSuccessor(LAST_PROCESSED_BLOCK(cfg),
                 LAST_LOOP_EXIT_IDX(cfg));
    cfg->lastProcessedIndex = LAST_LOOP_EXIT_IDX(cfg);
  }
  LS_PopLE(cfg->loopStack);
}

void CFG_EnterVarDec(CFG* cfg,
                 AST* node) {
  int varDecIndex = CFG_ConnectNewBlock(cfg, node);
  cfg->lastProcessedIndex = varDecIndex;
  cfg->blocks[varDecIndex]->opTree = OT_BuildFromAST(node);
  printf("CFG :: AST_VAR_DEC\n");
}

void CFG_EnterVarDef(CFG* cfg,
                 AST* node) {
  int varDefIndex = CFG_ConnectNewBlock(cfg, node);
  cfg->lastProcessedIndex = varDefIndex;
  printf("CFG :: AST_VAR_DEF\n");
}

void CFG_EnterAssignment(CFG* cfg,
                     AST* node) {
  int assignmentIndex = CFG_ConnectNewBlock(cfg, node);
  cfg->blocks[assignmentIndex]->opTree = OT_BuildFromAST(node);
  cfg->lastProcessedIndex = assignmentIndex;
}

void CFG_Walker(CFG* cfg, AST* node)
{
  if (!node) return;

  if (TOKEN_IS(node, "AST_IF"))
    CFG_EnterIf(cfg, node);

  if (TOKEN_IS(node, "AST_ELSE"))
    CFG_EnterElse(cfg, node);

  if (TOKEN_IS(node, "AST_LOOP"))
    CFG_EnterLoop(cfg, node);

  if (TOKEN_IS(node, "AST_REPEAT"))
    CFG_EnterRepeat(cfg, node);

  if (TOKEN_IS(node, "AST_BREAK"))
    CFG_EnterBreak(cfg, node);

  if (TOKEN_IS(node, "AST_ASSIGNMENT"))
    CFG_EnterAssignment(cfg,
                    node);

  if (TOKEN_IS(node, "AST_VAR_DEC"))
    CFG_EnterVarDec(cfg, node);

  if (TOKEN_IS(node, "AST_VAR_DEF"))
    CFG_EnterVarDec(cfg, node);

  if(!BREAK_DETECTED(cfg))
    for (int i = 0; i < node->childCount; i++)
      CFG_Walker(cfg, AST_GetChild(node, i));

  if (TOKEN_IS(node, "AST_CALL"))
    CFG_ExitCall(cfg, node);

  if (TOKEN_IS(node, "AST_LOOP"))
    CFG_ExitLoop(cfg, node);

  if (TOKEN_IS(node, "AST_REPEAT"))
    CFG_ExitRepeat(cfg, node);

  if (TOKEN_IS(node, "AST_IF"))
    CFG_ExitIf(cfg, node);

  if (TOKEN_IS(node, "AST_ELSE"))
    CFG_ExitElse(cfg, node);
}
