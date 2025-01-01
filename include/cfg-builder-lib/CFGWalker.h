#pragma once

#include "AST.h"
#include "CFG.h"

void cfgWalker(CFG* cfg,
               AST* node);

int connectNewBlock(CFG* cfg,
                    AST* current);

void enterIf(CFG* cfg,
             AST* node);
void exitIf(CFG* cfg,
            AST* node);

void enterElse(CFG* cfg,
               AST* node);
void exitElse(CFG* cfg,
              AST* node);

void enterLoop(CFG* cfg,
               AST* node);
void exitLoop(CFG* cfg,
              AST* node);

void enterRepeat(CFG* cfg,
                AST* node);
void exitRepeat(CFG* cfg,
                AST* node);

void enterVarDec(CFG* cfg,
                AST* node);

void enterVarDef(CFG* cfg,
                AST* node);

void enterBreak(CFG* cfg,
                AST* node);

void enterAssignment(CFG* cfg,
                    AST* node);
void exitCall(CFG* cfg,
              AST* node);
