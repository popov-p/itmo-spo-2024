grammar Var4;

options {
    language = C;
    backtrack = true;
    output = AST;
}

BOOL: 'true' | 'false';
IDENTIFIER: ('a'..'z' | 'A'..'Z' | '_') ('a'..'z' | 'A'..'Z' | '0'..'9' | '_')*;
STR: '"' (~('"'|'\\') | '\\' .)* '"';
CHAR : '\'' (~('\'') | '\\' .) '\'';
HEX : '0' ('x' | 'X') ( '0'..'9' | 'a'..'f' | 'A'..'F' )+;
BITS: '0' ('b' | 'B') ('0' | '1')+;
DEC: ('0'..'9')+;
ASSIGN : '=';
WS : (' ' | '\t' | '\r' | '\n')+ { };

source : sourceItem*;
sourceItem
    : funcDef
    ;

funcDef //ok
    : 'def' funcSignature statement* 'end'
    ;
    
funcSignature
    : IDENTIFIER '(' list_arg ')' ('of' typeRef)?
    ;

arg
    : IDENTIFIER ('of' typeRef)?
    ;

list_arg
    : (arg (',' arg)*)?
    ;
    
    typeRef
    : builtin
    | custom
    | arrayType
    ;

builtin
    : 'bool' | 'byte' | 'int' | 'uint' | 'long' | 'ulong' | 'char' | 'string'
    ;

custom
    : IDENTIFIER
    ;



arrayType
    : (builtin | custom) ('array' '[' DEC ']')*
    ;

    
statement
    : ifStatement
    | loopStatement
    | repeatStatement
    | breakStatement
    | expressionStatement
    | blockStatement
    ;

ifStatement
    : 'if' expr 'then' statement ('else' statement)?
    ;

loopStatement
    : ('while' | 'until') expr statement* 'end'
    ;

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
    : 'break' ';'
    ;

expressionStatement
    : expr ';'
    ;

blockStatement
    : ('begin' | '{') (statement | sourceItem)* ('end' | '}')
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

literalExpr
    : BOOL | STR | CHAR| HEX| BITS| DEC
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
    | '%'  
    ;

unOp
    : '-'   
    | '!'  
    | '~' 
    ;

