/** \file
 *  This C header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : /home/pavel/Projects/langparser/Lab-1/src/Sigma.g
 *     -                            On : 2024-10-20 11:30:20
 *     -                for the parser : SigmaParserParser
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser 
SigmaParser

has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 *
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pSigmaParser, which is returned from a call to SigmaParserNew().
 *
 * The methods in pSigmaParser are  as follows:
 *
 *  - 
 SigmaParser_source_return
      pSigmaParser->source(pSigmaParser)
 *  - 
 SigmaParser_sourceItem_return
      pSigmaParser->sourceItem(pSigmaParser)
 *  - 
 SigmaParser_funcDef_return
      pSigmaParser->funcDef(pSigmaParser)
 *  - 
 SigmaParser_funcSignature_return
      pSigmaParser->funcSignature(pSigmaParser)
 *  - 
 SigmaParser_arg_return
      pSigmaParser->arg(pSigmaParser)
 *  - 
 SigmaParser_list_arg_return
      pSigmaParser->list_arg(pSigmaParser)
 *  - 
 SigmaParser_typeRef_return
      pSigmaParser->typeRef(pSigmaParser)
 *  - 
 SigmaParser_builtin_return
      pSigmaParser->builtin(pSigmaParser)
 *  - 
 SigmaParser_custom_return
      pSigmaParser->custom(pSigmaParser)
 *  - 
 SigmaParser_arrayType_return
      pSigmaParser->arrayType(pSigmaParser)
 *  - 
 SigmaParser_arraySuffix_return
      pSigmaParser->arraySuffix(pSigmaParser)
 *  - 
 SigmaParser_baseType_return
      pSigmaParser->baseType(pSigmaParser)
 *  - 
 SigmaParser_statement_return
      pSigmaParser->statement(pSigmaParser)
 *  - 
 SigmaParser_variableDefinition_return
      pSigmaParser->variableDefinition(pSigmaParser)
 *  - 
 SigmaParser_variableDeclaration_return
      pSigmaParser->variableDeclaration(pSigmaParser)
 *  - 
 SigmaParser_ifStmt_return
      pSigmaParser->ifStmt(pSigmaParser)
 *  - 
 SigmaParser_elsePart_return
      pSigmaParser->elsePart(pSigmaParser)
 *  - 
 SigmaParser_loopStmt_return
      pSigmaParser->loopStmt(pSigmaParser)
 *  - 
 SigmaParser_repeatStmt_return
      pSigmaParser->repeatStmt(pSigmaParser)
 *  - 
 SigmaParser_repeatSuffix_return
      pSigmaParser->repeatSuffix(pSigmaParser)
 *  - 
 SigmaParser_breakStmt_return
      pSigmaParser->breakStmt(pSigmaParser)
 *  - 
 SigmaParser_expressionStmt_return
      pSigmaParser->expressionStmt(pSigmaParser)
 *  - 
 SigmaParser_blockStmt_return
      pSigmaParser->blockStmt(pSigmaParser)
 *  - 
 SigmaParser_blockStart_return
      pSigmaParser->blockStart(pSigmaParser)
 *  - 
 SigmaParser_blockEnd_return
      pSigmaParser->blockEnd(pSigmaParser)
 *  - 
 SigmaParser_statementList_return
      pSigmaParser->statementList(pSigmaParser)
 *  - 
 SigmaParser_assignmentStmt_return
      pSigmaParser->assignmentStmt(pSigmaParser)
 *  - 
 SigmaParser_returnStmt_return
      pSigmaParser->returnStmt(pSigmaParser)
 *  - 
 SigmaParser_expr_return
      pSigmaParser->expr(pSigmaParser)
 *  - 
 SigmaParser_binaryExpr_return
      pSigmaParser->binaryExpr(pSigmaParser)
 *  - 
 SigmaParser_unaryExpr_return
      pSigmaParser->unaryExpr(pSigmaParser)
 *  - 
 SigmaParser_call_return
      pSigmaParser->call(pSigmaParser)
 *  - 
 SigmaParser_slice_return
      pSigmaParser->slice(pSigmaParser)
 *  - 
 SigmaParser_braces_return
      pSigmaParser->braces(pSigmaParser)
 *  - 
 SigmaParser_place_return
      pSigmaParser->place(pSigmaParser)
 *  - 
 SigmaParser_bool_return
      pSigmaParser->bool(pSigmaParser)
 *  - 
 SigmaParser_literal_return
      pSigmaParser->literal(pSigmaParser)
 *  - 
 SigmaParser_ranges_return
      pSigmaParser->ranges(pSigmaParser)
 *  - 
 SigmaParser_list_expr_return
      pSigmaParser->list_expr(pSigmaParser)
 *  - 
 SigmaParser_list_range_return
      pSigmaParser->list_range(pSigmaParser)
 *  - 
 SigmaParser_binOp_return
      pSigmaParser->binOp(pSigmaParser)
 *  - 
 SigmaParser_unOp_return
      pSigmaParser->unOp(pSigmaParser)
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD license"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_SigmaParser_H
#define _SigmaParser_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct SigmaParser_Ctx_struct SigmaParser, * pSigmaParser;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/* ========================
 * BACKTRACKING IS ENABLED
 * ========================
 */

typedef struct SigmaParser_source_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_source_return;



typedef struct SigmaParser_sourceItem_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_sourceItem_return;



typedef struct SigmaParser_funcDef_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_funcDef_return;



typedef struct SigmaParser_funcSignature_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_funcSignature_return;



typedef struct SigmaParser_arg_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_arg_return;



typedef struct SigmaParser_list_arg_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_list_arg_return;



typedef struct SigmaParser_typeRef_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_typeRef_return;



typedef struct SigmaParser_builtin_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_builtin_return;



typedef struct SigmaParser_custom_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_custom_return;



typedef struct SigmaParser_arrayType_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_arrayType_return;



typedef struct SigmaParser_arraySuffix_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_arraySuffix_return;



typedef struct SigmaParser_baseType_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_baseType_return;



typedef struct SigmaParser_statement_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_statement_return;



typedef struct SigmaParser_variableDefinition_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_variableDefinition_return;



typedef struct SigmaParser_variableDeclaration_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_variableDeclaration_return;



typedef struct SigmaParser_ifStmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_ifStmt_return;



typedef struct SigmaParser_elsePart_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_elsePart_return;



typedef struct SigmaParser_loopStmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_loopStmt_return;



typedef struct SigmaParser_repeatStmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_repeatStmt_return;



typedef struct SigmaParser_repeatSuffix_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_repeatSuffix_return;



typedef struct SigmaParser_breakStmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_breakStmt_return;



typedef struct SigmaParser_expressionStmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_expressionStmt_return;



typedef struct SigmaParser_blockStmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_blockStmt_return;



typedef struct SigmaParser_blockStart_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_blockStart_return;



typedef struct SigmaParser_blockEnd_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_blockEnd_return;



typedef struct SigmaParser_statementList_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_statementList_return;



typedef struct SigmaParser_assignmentStmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_assignmentStmt_return;



typedef struct SigmaParser_returnStmt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_returnStmt_return;



typedef struct SigmaParser_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_expr_return;



typedef struct SigmaParser_binaryExpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_binaryExpr_return;



typedef struct SigmaParser_unaryExpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_unaryExpr_return;



typedef struct SigmaParser_call_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_call_return;



typedef struct SigmaParser_slice_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_slice_return;



typedef struct SigmaParser_braces_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_braces_return;



typedef struct SigmaParser_place_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_place_return;



typedef struct SigmaParser_bool_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_bool_return;



typedef struct SigmaParser_literal_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_literal_return;



typedef struct SigmaParser_ranges_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_ranges_return;



typedef struct SigmaParser_list_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_list_expr_return;



typedef struct SigmaParser_list_range_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_list_range_return;



typedef struct SigmaParser_binOp_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_binOp_return;



typedef struct SigmaParser_unOp_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    SigmaParser_unOp_return;




/** Context tracking structure for 
SigmaParser

 */
struct SigmaParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;

     SigmaParser_source_return
     (*source)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_sourceItem_return
     (*sourceItem)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_funcDef_return
     (*funcDef)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_funcSignature_return
     (*funcSignature)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_arg_return
     (*arg)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_list_arg_return
     (*list_arg)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_typeRef_return
     (*typeRef)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_builtin_return
     (*builtin)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_custom_return
     (*custom)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_arrayType_return
     (*arrayType)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_arraySuffix_return
     (*arraySuffix)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_baseType_return
     (*baseType)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_statement_return
     (*statement)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_variableDefinition_return
     (*variableDefinition)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_variableDeclaration_return
     (*variableDeclaration)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_ifStmt_return
     (*ifStmt)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_elsePart_return
     (*elsePart)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_loopStmt_return
     (*loopStmt)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_repeatStmt_return
     (*repeatStmt)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_repeatSuffix_return
     (*repeatSuffix)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_breakStmt_return
     (*breakStmt)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_expressionStmt_return
     (*expressionStmt)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_blockStmt_return
     (*blockStmt)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_blockStart_return
     (*blockStart)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_blockEnd_return
     (*blockEnd)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_statementList_return
     (*statementList)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_assignmentStmt_return
     (*assignmentStmt)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_returnStmt_return
     (*returnStmt)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_expr_return
     (*expr)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_binaryExpr_return
     (*binaryExpr)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_unaryExpr_return
     (*unaryExpr)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_call_return
     (*call)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_slice_return
     (*slice)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_braces_return
     (*braces)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_place_return
     (*place)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_bool_return
     (*bool)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_literal_return
     (*literal)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_ranges_return
     (*ranges)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_list_expr_return
     (*list_expr)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_list_range_return
     (*list_range)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_binOp_return
     (*binOp)	(struct SigmaParser_Ctx_struct * ctx);

     SigmaParser_unOp_return
     (*unOp)	(struct SigmaParser_Ctx_struct * ctx);

     ANTLR3_BOOLEAN
     (*synpred19_Sigma)	(struct SigmaParser_Ctx_struct * ctx);

     ANTLR3_BOOLEAN
     (*synpred22_Sigma)	(struct SigmaParser_Ctx_struct * ctx);

     ANTLR3_BOOLEAN
     (*synpred23_Sigma)	(struct SigmaParser_Ctx_struct * ctx);

     ANTLR3_BOOLEAN
     (*synpred24_Sigma)	(struct SigmaParser_Ctx_struct * ctx);

     ANTLR3_BOOLEAN
     (*synpred25_Sigma)	(struct SigmaParser_Ctx_struct * ctx);

     ANTLR3_BOOLEAN
     (*synpred26_Sigma)	(struct SigmaParser_Ctx_struct * ctx);

     ANTLR3_BOOLEAN
     (*synpred35_Sigma)	(struct SigmaParser_Ctx_struct * ctx);

     ANTLR3_BOOLEAN
     (*synpred37_Sigma)	(struct SigmaParser_Ctx_struct * ctx);

     ANTLR3_BOOLEAN
     (*synpred38_Sigma)	(struct SigmaParser_Ctx_struct * ctx);

     ANTLR3_BOOLEAN
     (*synpred40_Sigma)	(struct SigmaParser_Ctx_struct * ctx);
    // Delegated rules

    const char * (*getGrammarFileName)();
    void            (*reset)  (struct SigmaParser_Ctx_struct * ctx);
    void	    (*free)   (struct SigmaParser_Ctx_struct * ctx);
/* @headerFile.members() */
pANTLR3_BASE_TREE_ADAPTOR	adaptor;
pANTLR3_VECTOR_FACTORY		vectors;
/* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pSigmaParser SigmaParserNew         (
pANTLR3_COMMON_TOKEN_STREAM
 instream);
ANTLR3_API pSigmaParser SigmaParserNewSSD      (
pANTLR3_COMMON_TOKEN_STREAM
 instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the 
parser
 will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif
#define EOF      -1
#define T__49      49
#define T__50      50
#define T__51      51
#define T__52      52
#define T__53      53
#define T__54      54
#define T__55      55
#define T__56      56
#define T__57      57
#define T__58      58
#define T__59      59
#define T__60      60
#define T__61      61
#define T__62      62
#define T__63      63
#define T__64      64
#define T__65      65
#define T__66      66
#define T__67      67
#define T__68      68
#define T__69      69
#define T__70      70
#define T__71      71
#define T__72      72
#define T__73      73
#define T__74      74
#define T__75      75
#define T__76      76
#define T__77      77
#define T__78      78
#define T__79      79
#define T__80      80
#define T__81      81
#define ARG      4
#define ARR_TYPE      5
#define ASSIGN      6
#define BIN_OP      7
#define BITS      8
#define BLOCK      9
#define BOOL_T      10
#define BRACES      11
#define BREAK      12
#define BYTE_T      13
#define CALL      14
#define CHAR      15
#define CHAR_T      16
#define DEC      17
#define DIM      18
#define ELSE      19
#define EXPR      20
#define FALSE      21
#define FUNC_DEF      22
#define FUNC_SIG      23
#define HEX      24
#define IDENTIFIER      25
#define IF      26
#define INT_T      27
#define LIST_ARG      28
#define LIST_EXPR      29
#define LIST_RANGE      30
#define LONG_T      31
#define LOOP      32
#define PLACE_EXPR      33
#define RANGES      34
#define REPEAT      35
#define RETURN      36
#define SLICE      37
#define SOURCE      38
#define SOURCE_ITEM      39
#define STRING      40
#define STRING_T      41
#define TRUE      42
#define UINT_T      43
#define ULONG_T      44
#define UNARY_OP      45
#define VAR_DEC      46
#define VAR_DEF      47
#define WS      48
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for SigmaParser
 * =============================================================================
 */
/** } */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
