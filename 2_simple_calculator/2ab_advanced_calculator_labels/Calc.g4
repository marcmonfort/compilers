grammar Calc;

prog:  stat+ EOF ;

stat:  expr NEWLINE           # printExpr
    |  ID '=' expr NEWLINE    # assign
    |  NEWLINE                # blank
    ;

expr:  expr MUL expr    # prod
    |  expr ADD expr    # plus
    |  INT              # int
    |  ID               # id
    ;

MUL :  '*' ;
ADD :  '+' ;
ID  :  [a-zA-Z]+ ;       // match identifiers
INT :  [0-9]+ ;          // match integers
NEWLINE: '\r'? '\n' ;    // return newlines to parser (is end-statement signal)
WS  :  [ \t]+ -> skip ;  // toss out whitespace
