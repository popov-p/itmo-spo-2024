grammar V4;

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
  IF;
  ELSE;
  LIST_ARG;
  ARG;
  LOOP;
  BREAK;
  BLOCK;
  REPEAT;
  ARR_TYPE;
  CALL;
  SLICE;
  BRACES;
  RANGES;
  LIST_EXPR;
  LIST_RANGE;
  VAR_DEC;
  VAR_DEF;
  ASSIGNMENT;
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
  | expr
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
  : baseType
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
  : baseType arraySuffix -> ^(ARR_TYPE baseType arraySuffix)
  ;

arraySuffix
  : 'array' '[' DEC ']' arraySuffix -> ^(ARR_TYPE DEC arraySuffix)
  | 'array' '[' DEC ']' -> ^(ARR_TYPE DEC)
  ;


baseType
  : builtin
  | custom
  ;

statement
  : ifStmt
  | loopStmt
  | repeatStmt
  | breakStmt
  | returnStmt
  | blockStmt
  | expressionStmt
  | assignmentStmt
  | variableDeclaration
  | variableDefinition
  ;

expressionStmt
  : expr ';'
  -> ^(expr)
  ;
variableDefinition
  : typeRef IDENTIFIER ';' -> ^(VAR_DEF typeRef IDENTIFIER)
  ;

variableDeclaration
  : typeRef IDENTIFIER '=' expr ';' -> ^(VAR_DEC typeRef IDENTIFIER expr)
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
  -> ^(expr)
  ;

breakStmt
  : 'break' ';'
  -> ^(BREAK)
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
  : IDENTIFIER '=' expr ';' -> ^(ASSIGNMENT IDENTIFIER expr)
  ;

returnStmt
  : 'return' expr ';' -> ^(RETURN expr)
  | 'return' ';' -> ^(RETURN)
  ;

expr
  : comparisonExpression
  ;

comparisonExpression
  : additiveExpression (('>'^ | '<'^ | '>='^ | '<='^ | '=='^ | '!='^) additiveExpression)*
  ;

additiveExpression
  : multiplicativeExpression (('+'^ | '-'^) multiplicativeExpression)*
  ;

multiplicativeExpression
  : primaryExpression (('*'^ | '/'^) primaryExpression)*
  ;


primaryExpression
  : DEC
  | '(' additiveExpression ')' -> ^(additiveExpression)
  | call
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
  -> ^(LIST_RANGE (ranges)*)?
  ;
