grammar Sigma;

options {
  language = C;
  backtrack = true;
  output = AST;
}

tokens {
  FUNC_DEF;
  SOURCE;
  SOURCE_ITEM;
  FUNC_SIG;
  RETURN;
  ASSIGN;
  IF;
  ELSE;
  LIST_ARG;
  ARG;
  BIN_OP;
  PLACE_EXPR;
  LOOP;
  BREAK;
  BLOCK;
  REPEAT;
  ARR_TYPE;
  CALL;
  SLICE;
  UNARY_OP;
  BRACES;
  EXPR;
  RANGES;
  LIST_EXPR;
  LIST_RANGE;
  VAR_DEC;
  VAR_DEF;
}

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
  -> ^(FUNC_SIG IDENTIFIER list_arg (typeRef)?)
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
  : builtin 'array' '[' DEC ']' -> ^(ARR_TYPE builtin DEC)
  | custom 'array' '[' DEC ']' -> ^(ARR_TYPE custom DEC)
  ;

statement
  : ifStmt
  | loopStmt
  | repeatStmt
  | breakStmt
  | returnStmt
  | expressionStmt
  | blockStmt
  | assignmentStmt
  | variableDeclaration
  | variableDefinition
  ;

variableDefinition
  : typeRef IDENTIFIER ';' -> ^(VAR_DEF IDENTIFIER)
  ;

variableDeclaration
  : typeRef IDENTIFIER '=' expr ';' -> ^(VAR_DEC IDENTIFIER expr)
  ;

ifStmt
  : 'if' expr 'then' statement elsePart? -> ^(IF expr statement (elsePart)?)
  ;

elsePart
  : 'else' statement -> ^(ELSE statement)
  ;

loopStmt
  : ('while' | 'until') expr statement* 'end'
  -> ^(LOOP expr statement*)
  ;

repeatStmt
  : blockStmt repeatSuffix
  -> ^(REPEAT blockStmt repeatSuffix)
  ;

repeatSuffix
  : ('while' | 'until') expr ';'
  -> ^(EXPR expr)
  ;

breakStmt
  : 'break' ';'
  -> ^(BREAK)
  ;

expressionStmt
  : expr ';' -> ^(EXPR expr)
  ;

blockStmt
  : blockStart statementList blockEnd
  -> ^(BLOCK statementList)
  ;

blockStart
  : ('begin' | '{')
  ;

blockEnd
  : ('end' | '}')
  ;

statementList
  : (statement | sourceItem)*
  ;

assignmentStmt
  : IDENTIFIER '=' expr ';' -> ^(ASSIGN IDENTIFIER expr)
  ;

returnStmt
  : 'return' expr ';' -> ^(RETURN expr)
  | 'return' ';' -> ^(RETURN)
  ;

expr
  : binaryExpr
  | unaryExpr
  ;

binaryExpr
  : unaryExpr (binOp unaryExpr)*
  -> ^(binOp unaryExpr (unaryExpr)*)
  ;

unaryExpr
  : call
  | slice
  | braces
  | place
  | literal
  ;

call
  : IDENTIFIER '(' list_expr ')'
  -> ^(CALL IDENTIFIER list_expr)
  ;

slice
  : IDENTIFIER '[' list_range ']' -> ^(SLICE IDENTIFIER list_range)
  ;

braces
  : '(' expr ')' -> ^(BRACES expr)
  ;

place
  : IDENTIFIER -> ^(IDENTIFIER)
  ;

bool
  : TRUE
  | FALSE
  ;

literal
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
//  -> ^(LIST_RANGE (ranges)*)?
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
