grammar T;

options {
    language = C;
}


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
    
BOOL
    :   'true' | 'false'
    ;
