grammar Var4;

//it`s a testing field

options {
  language = C;
  backtrack = true;
  output = AST;
}

tokens {
  FUNC_DEF;
  SOURCE;
  SOURCE_ITEM;
  FUNC_SIGNATURE;
  RETURN;
  ASSIGNMENT;
  IF;
  LIST_ARG;
  ARG;
  BIN_OP;
  PLACE_EXPR;
  LOOP;
  BREAK;
  BLOCK;
  REPEAT;
  ARRAY_TYPE;
  CALL;
  SLICE;
  UNARY_OP;
  BRACES_EXPR;
  EXPR;
  RANGES;
  LIST_EXPR;
  LIST_RANGE;
  VAR_DEC;
  VAR_DEF;
}

//specific keywords Var4

TRUE: 'true';
FALSE: 'false';
BYTE_T: 'byte';
INT_T: 'int';
UINT_T: 'uint';
LONG_T: 'long';
ULONG_T: 'ulong';
CHAR_T: 'char';
STRING_T: 'string';
BOOL_T: 'boolean';


//common part

IDENTIFIER: ('a'..'z' | 'A'..'Z' | '_') ('a'..'z' | 'A'..'Z' | '0'..'9' | '_')*;
STRING: '"' (~('"'|'\\') | '\\' .)* '"';
CHAR: '\'' (~('\'') | '\\' .) '\'';
HEX: '0' ('x' | 'X') ( '0'..'9' | 'a'..'f' | 'A'..'F' )+;
BITS: '0' ('b' | 'B') ('0' | '1')+;
DEC: ('0'..'9')+;
WS: (' ' | '\t' | '\n')+ { $channel = HIDDEN; };

source
  : sourceItem* -> ^(SOURCE sourceItem*)
  ;
sourceItem
  : funcDef -> ^(SOURCE_ITEM funcDef)
  ;

funcDef
  : 'def' funcSignature statement* 'end'
  -> ^(FUNC_DEF funcSignature statement*)
  ;

funcSignature
  : IDENTIFIER '(' list_arg ')' ('of' typeRef)?
  -> ^(FUNC_SIGNATURE IDENTIFIER list_arg (typeRef)?)
  ;

arg
  : IDENTIFIER ('of' typeRef)?
  -> ^(ARG IDENTIFIER (typeRef)?)
  ;

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
  : builtin 'array' '[' DEC ']' -> ^(ARRAY_TYPE builtin DEC)
  | custom 'array' '[' DEC ']' -> ^(ARRAY_TYPE custom DEC)
  ;

statement
  : ifStatement
  | loopStatement
  | repeatStatement
  | breakStatement
  | returnStatement
  | expressionStatement
  | blockStatement -> ^(BLOCK blockStatement)
  | assignmentStatement
  | variableDeclaration
  | variableDefinition
  ;

variableDefinition
  : typeRef IDENTIFIER ';' -> ^(VAR_DEF IDENTIFIER)
  ;

variableDeclaration
  : typeRef IDENTIFIER '=' expr ';' -> ^(VAR_DEC IDENTIFIER expr)
  ;

ifStatement
  : 'if' expr 'then' statement ('else' statement)?
  -> ^(IF expr statement (statement)?)
  ;

loopStatement
  : ('while' | 'until') expr statement* 'end'
  -> ^(LOOP expr statement*)
  ;

repeatStatement
  : baseStatement repeatSuffix
  -> ^(REPEAT baseStatement repeatSuffix)
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
  : 'break' ';'
  -> ^(BREAK)
  ;

expressionStatement
  : expr ';'
  ;

blockStatement
  : ('begin' | '{') (statement | sourceItem)* ('end' | '}')
  ;

assignmentStatement
  : IDENTIFIER '=' expr ';' -> ^(ASSIGNMENT IDENTIFIER expr)
  ;

returnStatement
  : 'return' expr ';' -> ^(RETURN expr)
  ;

expr
  : primaryExpr rest
  -> ^(EXPR primaryExpr rest)
  ;

rest
  : (binaryOpSuffix | callSuffix | sliceSuffix)*
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
  : '(' list_expr ')' -> ^(CALL list_expr)
  ;

sliceSuffix
  : '[' list_range ']' -> ^(SLICE list_range)
  ;

unaryExpr
  : unOp primaryExpr -> ^(UNARY_OP unOp primaryExpr)
  ;

bracesExpr
  : '(' expr ')' -> ^(BRACES_EXPR expr)
  ;

placeExpr
  : IDENTIFIER -> ^(IDENTIFIER)
  ;

bool
  : TRUE | FALSE
  ;

literalExpr
  : bool -> ^(bool)
  | STRING -> ^(STRING)
  | CHAR -> ^(CHAR)
  | HEX -> ^(HEX)
  | BITS -> ^(BITS)
  | DEC -> ^(DEC)
  ;

ranges
  : expr ('..' expr)?
  -> ^(RANGES expr (expr)?)
  ;


list_expr
  : (expr (',' expr)*)?
  -> ^(LIST_EXPR (expr)*)?
  ;


list_range
  : (ranges (',' ranges)*)?
  -> ^(LIST_RANGE (ranges)*)?
  ;

binOp
  : '+' -> ^('+')
  | '-' -> ^('-')
  | '*' -> ^('*')
  | '/' -> ^('/')
  | '>' -> ^('>')
  | '<' -> ^('<')
  | '>=' -> ^('>=')
  | '<=' -> ^('<=')
  | '==' -> ^('==')
  ;

unOp
  : '-' -> ^('-')
  | '!' -> ^('!')
  | '~' -> ^('~')
  ;
