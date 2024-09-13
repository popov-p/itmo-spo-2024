grammar T;

options {
    language = C;
    backtrack = true;
   output = AST;
}

BOOL
    :   'true' | 'false'
    ;

IDENTIFIER
    :   ('a'..'z' | 'A'..'Z' | '_') ('a'..'z' | 'A'..'Z' | '0'..'9' | '_')*
    ;

STRING
    :   '"' ( '\\' . | ~('\\'|'"') )* '"'
    ;

HEX
    :   '0' ('x' | 'X') ('0'..'9' | 'A'..'F' | 'a'..'f')+
    ;

BITS
    :   '0' ('b' | 'B') ('0' | '1')+
    ;

DEC
    :   '0'..'9'+
    ;
 
source
    : sourceItem*
    ;
    
//typeRef
typeRef
    : baseType arraySuffix
    | IDENTIFIER arraySuffix
    ;

baseType
    : 'bool'
    | 'byte'
    | 'int'
    | 'uint'
    | 'long'
    | 'ulong'
    | 'char'
    | 'string'
    ;

arraySuffix
    : '[' arrayContents? ']'
    | /* пусто, чтобы завершить рекурсию */
    ;

arrayContents
    : arrayElement (',' arrayElement)*
    ;

arrayElement
    : typeRef
    ;

//-----------

//funcSignature
funcSignature
    : typeRef?  IDENTIFIER'(' argDefList ')' 
    ;

argDefList
    : argDef (',' argDef)*
    ;

argDef
    : typeRef? IDENTIFIER
    ;
 //------------------
//sourceItem
sourceItem
    :  funcDef
    ;
funcDef
    : funcSignature (block| ' ; ')
    ;
//--------------

//statement
statement
    : block
    ;
    
    block
    : '{' statement* '}'
    ;
//-------------
 // expr   
// Основное выражение
expr
    : unary exprSuffix?    // Унарные операции, с возможным продолжением бинарных операций
    ;

// Обработка бинарных операций
exprSuffix
    : binOp unary exprSuffix?    // Правая рекурсия для бинарных операций
    ;

// Унарные операции и базовые выражения
unary
    : unOp unary                // Унарные операции рекурсивно применяются
    | primary                   // Базовые выражения без унарных операторов
    ;

// Основные базовые выражения
primary
    : place
    | literal
    | braces
    | primarySuffix             // Для вызовов функций и индексирования
    ;

// Продолжения для вызовов функций и индексирования
primarySuffix
    : callSuffix
    | indexerSuffix
    ;

// Вызов функции
callSuffix
    : '(' exprList ')'
    ;

// Индексирование
indexerSuffix
    : '[' exprList ']'
    ;

// Списки выражений, разделённых запятыми
exprList
    : expr (',' expr)*
    |                     // Пустой список
    ;

// Унарные и бинарные операторы
binOp
    : '+'    // Сложение
    | '-'    // Вычитание
    | '*'    // Умножение
    | '/'    // Деление
    | '%'    // Остаток от деления
    | '&&'   // Логическое И
    | '||'   // Логическое ИЛИ
    | '=='   // Равенство
    | '!='   // Неравенство
    | '<'    // Меньше
    | '>'    // Больше
    | '<='   // Меньше или равно
    | '>='   // Больше или равно
    ;

// Унарные операторы
unOp
    : '+'    // Унарный плюс
    | '-'    // Унарный минус
    | '!'    // Логическое отрицание
    | '~'    // Побитовое отрицание
    ;

// Лексемы для идентификаторов и литералов
place
    : IDENTIFIER
    ;

literal
    : BOOL
    | STRING
    | HEX
    | BITS
    | DEC
    ;

// Округляющие скобки
braces
    : '(' expr ')'
    ;
//-------    