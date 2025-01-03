#pragma once

#include "AST.h"
#include "CFG.h"

void CFG_Walker(CFG* cfg,
                AST* node);

int CFG_ConnectNewBlock(CFG* cfg,
                    AST* current);

void CFG_EnterIf(CFG* cfg,
                 AST* node);

void CFG_ExitIf(CFG* cfg,
                AST* node);

void CFG_EnterElse(CFG* cfg,
                   AST* node);

void CFG_ExitElse(CFG* cfg,
                  AST* node);

void CFG_EnterLoop(CFG* cfg,
                   AST* node);
void CFG_ExitLoop(CFG* cfg,
                  AST* node);

void CFG_EnterRepeat(CFG* cfg,
                     AST* node);
void CFG_ExitRepeat(CFG* cfg,
                    AST* node);

void CFG_EnterVarDec(CFG* cfg,
                     AST* node);

void CFG_EnterVarDef(CFG* cfg,
                     AST* node);

void CFG_EnterBreak(CFG* cfg,
                    AST* node);

void CFG_EnterAssignment(CFG* cfg,
                         AST* node);
void CFG_ExitCall(CFG* cfg,
                  AST* node);
