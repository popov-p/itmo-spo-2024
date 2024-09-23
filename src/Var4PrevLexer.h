/** \file
 *  This C header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : ../src/Var4Prev.g
 *     -                            On : 2024-09-23 21:48:02
 *     -                 for the lexer : Var4PrevLexerLexer
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The lexer 
Var4PrevLexer

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
 * a parser context typedef pVar4PrevLexer, which is returned from a call to Var4PrevLexerNew().
 *
 * As this is a generated lexer, it is unlikely you will call it 'manually'. However
 * the methods are provided anyway.
 *
 * The methods in pVar4PrevLexer are  as follows:
 *
 *  - 
 void
      pVar4PrevLexer->TRUE(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->FALSE(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->DEF(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->BEGIN(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->END(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->OF(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->LPAREN(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->RPAREN(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->COMMA(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->ARRAY(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->LSQBRACK(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->RSQBRACK(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->IF(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->ELSE(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->THEN(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->RETURN(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->WHILE(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->UNTIL(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->SEMICOLON(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->BREAK(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->LCURLBRACK(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->RCURLBRACK(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->RANGEDOTS(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->BYTE_T(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->INT_T(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->UINT_T(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->LONG_T(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->ULONG_T(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->CHAR_T(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->STRING_T(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->BOOL_T(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->ASSIGN(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->PLUS(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->MINUS(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->MUL(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->DIV(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->GREATER(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->LESS(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->GEQ(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->LEQ(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->EQUAL(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->LOGICNOT(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->BYTENOT(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->IDENTIFIER(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->STRING(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->CHAR(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->HEX(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->BITS(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->DEC(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->WS(pVar4PrevLexer)
 *  - 
 void
      pVar4PrevLexer->Tokens(pVar4PrevLexer)
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

#ifndef	_Var4PrevLexer_H
#define _Var4PrevLexer_H
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
typedef struct Var4PrevLexer_Ctx_struct Var4PrevLexer, * pVar4PrevLexer;



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

/** Context tracking structure for 
Var4PrevLexer

 */
struct Var4PrevLexer_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_LEXER    pLexer;

     void
     (*mTRUE)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mFALSE)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mDEF)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mBEGIN)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mEND)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mOF)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mLPAREN)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mRPAREN)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mCOMMA)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mARRAY)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mLSQBRACK)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mRSQBRACK)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mIF)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mELSE)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mTHEN)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mRETURN)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mWHILE)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mUNTIL)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mSEMICOLON)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mBREAK)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mLCURLBRACK)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mRCURLBRACK)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mRANGEDOTS)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mBYTE_T)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mINT_T)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mUINT_T)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mLONG_T)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mULONG_T)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mCHAR_T)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mSTRING_T)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mBOOL_T)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mASSIGN)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mPLUS)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mMINUS)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mMUL)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mDIV)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mGREATER)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mLESS)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mGEQ)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mLEQ)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mEQUAL)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mLOGICNOT)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mBYTENOT)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mIDENTIFIER)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mSTRING)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mCHAR)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mHEX)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mBITS)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mDEC)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mWS)	(struct Var4PrevLexer_Ctx_struct * ctx);

     void
     (*mTokens)	(struct Var4PrevLexer_Ctx_struct * ctx);
    const char * (*getGrammarFileName)();
    void            (*reset)  (struct Var4PrevLexer_Ctx_struct * ctx);
    void	    (*free)   (struct Var4PrevLexer_Ctx_struct * ctx);
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pVar4PrevLexer Var4PrevLexerNew         (
pANTLR3_INPUT_STREAM
 instream);
ANTLR3_API pVar4PrevLexer Var4PrevLexerNewSSD      (
pANTLR3_INPUT_STREAM
 instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the 
lexer
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
#define ARG      4
#define ARRAY      5
#define ASSIGN      6
#define ASSIGNMENT_STATEMENT      7
#define BEGIN      8
#define BIN_OP      9
#define BITS      10
#define BOOL_T      11
#define BREAK      12
#define BYTENOT      13
#define BYTE_T      14
#define CHAR      15
#define CHAR_T      16
#define COMMA      17
#define DEC      18
#define DEF      19
#define DIV      20
#define ELSE      21
#define END      22
#define EQUAL      23
#define FALSE      24
#define FUNC_DEF      25
#define FUNC_SIGNATURE      26
#define GEQ      27
#define GREATER      28
#define HEX      29
#define IDENTIFIER      30
#define IF      31
#define IF_STATEMENT      32
#define INT_T      33
#define LCURLBRACK      34
#define LEQ      35
#define LESS      36
#define LIST_ARG      37
#define LITERAL      38
#define LOGICNOT      39
#define LONG_T      40
#define LPAREN      41
#define LSQBRACK      42
#define MINUS      43
#define MUL      44
#define OF      45
#define PLACE_EXPR      46
#define PLUS      47
#define RANGEDOTS      48
#define RCURLBRACK      49
#define RETURN      50
#define RETURN_STATEMENT      51
#define RPAREN      52
#define RSQBRACK      53
#define SEMICOLON      54
#define SOURCE      55
#define SOURCE_ITEM      56
#define STRING      57
#define STRING_T      58
#define THEN      59
#define TRUE      60
#define UINT_T      61
#define ULONG_T      62
#define UNTIL      63
#define WHILE      64
#define WS      65
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for Var4PrevLexer
 * =============================================================================
 */
/** } */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
