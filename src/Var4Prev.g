grammar Var4Prev;
//fornow it is equal to var4 grammar but its a testing field
options {
  language = C;
  backtrack = true;
  output = AST;
}

tokens {
  FUNC_DEF;
  SOURCE;
  SOURCE_ITEM;
  PLUS;
  MINUS;
  GREATER;
  FUNC_SIGNATURE;
  RETURN_STATEMENT;
  ASSIGNMENT_STATEMENT;
  IF_STATEMENT;
  LIST_ARG;
  ARG;
  BIN_OP;
  LITERAL;
  PLACE_EXPR;
  LOOP_STATEMENT;
  EXPRESSION_STATEMENT;
  BREAK_STATEMENT;
  BLOCK_STATEMENT;
  REPEAT_STATEMENT;
}

//specific keywords Var4
TRUE: 'true';
FALSE: 'false';
DEF: 'def';
END: 'end';
OF: 'of';
LPAREN: '(';
RPAREN: ')';
COMMA: ',';
ARRAY: 'array';
LSQBRACK: '[';
RSQBRACK: ']';
IF: 'if';
ELSE: 'else';
THEN: 'then';
RETURN: 'return';
WHILE: 'while';
UNTIL: 'until';
SEMICOLON: ';';
BREAK: 'break';
LCURLBRACK: '{';
RCURLBRACK: '}';
RANGEDOTS: '..';
BYTE_T: 'byte';
INT_T: 'int';
UINT_T: 'uint';
LONG_T: 'long';
ULONG_T: 'ulong';
CHAR_T: 'char';
STRING_T: 'string';
BOOL_T: 'boolean';

ASSIGN: '=';
PLUS: '+';
MINUS: '-';
MUL: '*';
DIV: '/';
GREATER: '>';
LESS: '<';
GEQ: '>=';
LEQ: '<=';
EQUAL: '==';
LOGICNOT: '!';
BYTENOT: '~';
BEGIN: 'begin';
//-----------------------

//common part

IDENTIFIER: ('a'..'z' | 'A'..'Z' | '_') ('a'..'z' | 'A'..'Z' | '0'..'9' | '_')*;
STRING: '"' (~('"'|'\\') | '\\' .)* '"';
CHAR: '\'' (~('\'') | '\\' .) '\'';
HEX: '0' ('x' | 'X') ( '0'..'9' | 'a'..'f' | 'A'..'F' )+;
BITS: '0' ('b' | 'B') ('0' | '1')+;
DEC: ('0'..'9')+;
WS: (' ' | '\t' | '\n')+ { $channel = HIDDEN; };
//--------------------

source : sourceItem* -> ^(SOURCE sourceItem*);
sourceItem : funcDef -> ^(SOURCE_ITEM funcDef);

funcDef
  : 'def' funcSignature statement* 'end'
  -> ^(FUNC_DEF funcSignature statement*);

funcSignature :
  IDENTIFIER '(' list_arg ')' (OF typeRef)?
  -> ^(FUNC_SIGNATURE IDENTIFIER list_arg (typeRef)?);

arg : IDENTIFIER (OF typeRef)?
    -> ^(ARG IDENTIFIER (typeRef)?);

list_arg
  : arg (',' arg)*
  -> ^(LIST_ARG arg (arg)*)
  |
  -> ^(LIST_ARG)
  ;


typeRef
  : builtin
  | custom
  | arrayType
  ;

builtin
  : BOOL_T -> ^(BOOL_T)
  | BYTE_T -> ^(BYTE_T)
  | INT_T -> ^(INT_T)
  | UINT_T -> ^(UINT_T)
  | LONG_T -> ^(LONG_T)
  | ULONG_T -> ^(ULONG_T)
  | CHAR_T -> ^(CHAR_T)
  | STRING_T -> ^(STRING_T)
  ;


custom
  : IDENTIFIER -> ^(IDENTIFIER)
  ;


arrayType
  : (builtin | custom) ('array' '[' DEC ']')*
  ;


statement
  : ifStatement -> ^(IF_STATEMENT ifStatement)
  | loopStatement -> ^(LOOP_STATEMENT loopStatement)
  | repeatStatement -> ^(REPEAT_STATEMENT repeatStatement)
  | breakStatement -> ^(BREAK_STATEMENT breakStatement)
  | returnStatement -> ^(RETURN_STATEMENT returnStatement)
  | expressionStatement -> ^(EXPRESSION_STATEMENT expressionStatement)
  | blockStatement -> ^(BLOCK_STATEMENT blockStatement)
  | assignmentStatement -> ^(ASSIGNMENT_STATEMENT assignmentStatement)
  ;


ifStatement
  : 'if' expr 'then' statement ('else' statement)?;

loopStatement
  : ('while' | 'until') expr statement* 'end';


repeatStatement
  : baseStatement repeatSuffix
  ;

repeatSuffix
  : ('while' | 'until') expr ';'
  ;

baseStatement
  : breakStatement
  | expressionStatement
  | blockStatement
  ;

breakStatement
  : 'break' ';';

expressionStatement
  : expr ';';


blockStatement
  : ('begin' | '{') (statement | sourceItem)* ('end' | '}')
  ;


assignmentStatement
  : IDENTIFIER '=' expr ';';

returnStatement
  : 'return' expr ';';

expr
  : primaryExpr (binaryOpSuffix | callSuffix | sliceSuffix)*
  ;

primaryExpr
  : unaryExpr
  | bracesExpr
  | placeExpr
  | literalExpr
  ;

binaryOpSuffix
  : binOp primaryExpr
  -> ^(BIN_OP binOp primaryExpr)
  ;

callSuffix
  : '(' list_expr ')'
  ;

sliceSuffix
  : '[' list_range ']'
  ;

unaryExpr
  : unOp primaryExpr
  ;

bracesExpr
  : '(' expr ')'
  ;

placeExpr
  : IDENTIFIER
  ;

bool: TRUE | FALSE;

literalExpr
  : bool -> ^(LITERAL bool)
  | STRING -> ^(LITERAL STRING)
  | CHAR -> ^(LITERAL CHAR)
  | HEX -> ^(LITERAL HEX)
  | BITS -> ^(LITERAL BITS)
  | DEC -> ^(LITERAL DEC)
  ;

ranges
  : expr ('..' expr)?
  ;

list_expr
  : (expr (',' expr)*)?
  ;

list_range
  : (ranges (',' ranges)*)?
  ;


binOp
  : '+'
  | '-'
  | '*'
  | '/'
  | '>'
  | '<'
  | '>='
  | '<='
  | '=='
  ;


unOp
  : '-' -> ^('-')
  | '!' -> ^('!')
  | '~' -> ^('~')
  ;

