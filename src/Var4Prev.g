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
  : DEF funcSignature statement* END
  -> ^(FUNC_DEF funcSignature statement*);

funcSignature :
  IDENTIFIER '(' list_arg ')' (OF typeRef)?
  -> ^(FUNC_SIGNATURE IDENTIFIER list_arg (typeRef)?);

arg : IDENTIFIER (OF typeRef)?
    -> ^(ARG IDENTIFIER (typeRef)?);

list_arg
  : arg (COMMA arg)*
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
  : (builtin | custom) (ARRAY LSQBRACK DEC RSQBRACK)*
  ;


statement
  : ifStatement
  | loopStatement
  | repeatStatement
  | breakStatement
  | returnStatement
  | expressionStatement
  | blockStatement
  | assignmentStatement
  ;

ifStatement
  : IF expr THEN statement (ELSE statement)?
  -> ^(IF_STATEMENT expr statement (ELSE statement)?);

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
  -> ^(ASSIGNMENT_STATEMENT IDENTIFIER expr)
  ;

returnStatement
  : RETURN expr SEMICOLON
  -> ^(RETURN_STATEMENT expr)
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
  -> ^(BIN_OP binOp primaryExpr)
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
  : bool -> ^(LITERAL bool)
  | STRING -> ^(LITERAL STRING)
  | CHAR -> ^(LITERAL CHAR)
  | HEX -> ^(LITERAL HEX)
  | BITS -> ^(LITERAL BITS)
  | DEC -> ^(LITERAL DEC)
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
  | GREATER
  | LESS
  | GEQ
  | LEQ
  | EQUAL
  ;


unOp
  : MINUS -> ^(MINUS)
  | LOGICNOT -> ^(LOGICNOT)
  | BYTENOT -> ^(BYTENOT)
  ;

