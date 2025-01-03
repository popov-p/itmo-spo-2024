grammar V4;

options {
  language = C;
  backtrack = true;
  output = AST;
}

tokens {
  AST_FUNC_DEF;
  AST_SOURCE;
  AST_SOURCE_ITEM;
  AST_FUNC_SIG;
  AST_RETURN;
  AST_IF;
  AST_ELSE;
  AST_LIST_ARG;
  AST_ARG;
  AST_LOOP;
  AST_BREAK;
  AST_BLOCK;
  AST_REPEAT;
  AST_ARR_TYPE;
  AST_CALL;
  AST_SLICE;
  AST_BRACES;
  AST_RANGES;
  AST_LIST_EXPR;
  AST_LIST_RANGE;
  AST_VAR_DEC;
  AST_VAR_DEF;
  AST_ASSIGNMENT;
  AST_PLUS;
  AST_MINUS;
  AST_MUL;
  AST_DIV;
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
  : sourceItem* -> ^(AST_SOURCE sourceItem*)
  ;

sourceItem
  : funcDef -> ^(AST_SOURCE_ITEM funcDef)
  ;

funcDef
  : 'def' funcSignature statement* 'end'
  -> ^(AST_FUNC_DEF funcSignature statement*)
  ;

funcSignature
  : IDENTIFIER '(' list_arg ')' ('of' typeRef)?
  -> ^(AST_FUNC_SIG IDENTIFIER list_arg (typeRef)?)
  ;

arg
  : IDENTIFIER ('of' typeRef)?
  -> ^(AST_ARG IDENTIFIER (typeRef)?)
  ;

list_arg
  : arg (',' arg)*
  -> ^(AST_LIST_ARG arg (arg)*)
  |
  -> ^(AST_LIST_ARG)
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
  : baseType arraySuffix -> ^(AST_ARR_TYPE baseType arraySuffix)
  ;

arraySuffix
  : 'array' '[' DEC ']' arraySuffix -> ^(AST_ARR_TYPE DEC arraySuffix)
  | 'array' '[' DEC ']' -> ^(AST_ARR_TYPE DEC)
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
  : typeRef IDENTIFIER ';' -> ^(AST_VAR_DEF typeRef IDENTIFIER)
  ;

variableDeclaration
  : typeRef IDENTIFIER '=' expr ';' -> ^(AST_VAR_DEC typeRef IDENTIFIER expr)
  ;

ifStmt
  : 'if' expr 'then' statement elsePart? -> ^(AST_IF expr statement (elsePart)?)
  ;

elsePart
  : 'else' statement -> ^(AST_ELSE statement)
  ;

loopStmt
  : ('while' | 'until') expr statement* 'end'
  -> ^(AST_LOOP expr statement*)
  ;

repeatStmt
  : blockStmt repeatSuffix
  -> ^(AST_REPEAT blockStmt repeatSuffix)
  ;

repeatSuffix
  : ('while' | 'until') expr ';'
  -> ^(expr)
  ;

breakStmt
  : 'break' ';'
  -> ^(AST_BREAK)
  ;


blockStmt
  : blockStart statementList blockEnd
  -> ^(AST_BLOCK statementList)
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
  : IDENTIFIER '=' expr ';' -> ^(AST_ASSIGNMENT IDENTIFIER expr)
  ;

returnStmt
  : 'return' expr ';' -> ^(AST_RETURN expr)
  | 'return' ';' -> ^(AST_RETURN)
  ;

expr
  : comparisonExpression
  ;

comparisonExpression
  : additiveExpression (('>'^ | '<'^ | '>='^ | '<='^ | '=='^ | '!='^) additiveExpression)*
  ;

additiveOperation
  : '+' -> ^(AST_PLUS)
  | '-' -> ^(AST_MINUS)
  ;

multiplicativeOperation
  : '*' -> ^(AST_MUL)
  | '/' -> ^(AST_DIV)
  ;

additiveExpression
  : multiplicativeExpression ((additiveOperation^) multiplicativeExpression)*
  ;

multiplicativeExpression
  : primaryExpression ((multiplicativeOperation^) primaryExpression)*
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
  -> ^(AST_CALL IDENTIFIER list_expr)
  ;

slice
  : IDENTIFIER '[' list_range ']' -> ^(AST_SLICE IDENTIFIER list_range)
  ;

braces
  : '(' expr ')' -> ^(AST_BRACES expr)
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
  -> ^(AST_RANGES expr (expr)?)
  ;

list_expr
  : (expr (',' expr)*)?
  -> ^(AST_LIST_EXPR (expr)*)?
  ;

list_range
  : (ranges (',' ranges)*)?
  -> ^(AST_LIST_RANGE (ranges)*)?
  ;
