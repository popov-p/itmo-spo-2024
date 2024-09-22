grammar Var4;

options {
  language = C;
  backtrack = true;
  output = AST;
}

//specific keywords Var4
TRUE: 'true';
FALSE: 'false';
DEF: 'def';
BEGIN: 'begin';
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
LOGICNOT: '!';
BYTENOT: '~';
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

source : sourceItem*;
sourceItem : funcDef;

funcDef : DEF funcSignature statement* END;
    
funcSignature : IDENTIFIER LPAREN list_arg RPAREN (OF typeRef)?;

arg : IDENTIFIER (OF typeRef)?;

list_arg : (arg (COMMA arg)*)?;
typeRef
  : builtin
  | custom
  | arrayType
  ;

builtin
  : BOOL_T | BYTE_T | INT_T | UINT_T | LONG_T | ULONG_T | CHAR_T | STRING_T
  ;

custom
  : IDENTIFIER
  ;



arrayType
  : (builtin | custom) (ARRAY LSQBRACK DEC RSQBRACK)*
  ;


statement
  : ifStatement
  | loopStatement
  | repeatStatement
  | breakStatement
  | expressionStatement
  | blockStatement
  | assignmentStatement
  ;

ifStatement
  : IF expr THEN statement (ELSE statement)?
  ;

loopStatement
  : (WHILE | UNTIL) expr statement* END
  ;

repeatStatement
  : baseStatement repeatSuffix
  ;

repeatSuffix
  : (WHILE | UNTIL) expr SEMICOLON
  ;

baseStatement
  : breakStatement
  | expressionStatement
  | blockStatement
  ;

breakStatement
  : BREAK SEMICOLON
  ;

expressionStatement
  : expr SEMICOLON
  ;

blockStatement
  : (BEGIN | LCURLBRACK) (statement | sourceItem)* (END | RCURLBRACK)
  ;

assignmentStatement
  : IDENTIFIER ASSIGN expr SEMICOLON
  ;

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
  ;

callSuffix
  : LPAREN list_expr RPAREN
  ;

sliceSuffix
  : LSQBRACK list_range RSQBRACK
  ;

unaryExpr
  : unOp primaryExpr
  ;

bracesExpr
  : LPAREN expr RPAREN
  ;

placeExpr
  : IDENTIFIER
  ;

bool: TRUE | FALSE;

literalExpr
  : bool | STRING | CHAR | HEX | BITS | DEC
  ;

ranges
  : expr (RANGEDOTS expr)?
  ;

list_expr
  : (expr (COMMA expr)*)?
  ;

list_range
  : (ranges (COMMA ranges)*)?
  ;


binOp
  : PLUS
  | MINUS
  | MUL
  | DIV
  ;

unOp
  : MINUS
  | LOGICNOT
  | BYTENOT
  ;

