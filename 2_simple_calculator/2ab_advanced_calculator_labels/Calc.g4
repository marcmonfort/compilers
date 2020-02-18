grammar Calc;

prog:  stat+ EOF ;

stat:  expr NEWLINE                                 # printExpr
    |  ID '=' expr NEWLINE                          # assign
    |  IF expr THEN stat+ else1 ENDIF                # if
    |  NEWLINE                                      # blank
    ;
    
else1: (ELSE stat+ | )
    ;

expr:  SUB expr                             # not
    |  LPAR expr RPAR                       # par
    |  expr (MUL|DIV) expr                  # prod
    |  expr (ADD|SUB) expr                  # plus
    |  (MAX|MIN) LPAR expr ',' expr RPAR    # max
    |  expr (EQ|NEQ|LT|GT) expr             # comp
    |  INT                                  # int
    |  ID                                   # id
    ;
    

    
    
MUL :  '*' ;
ADD :  '+' ;

DIV :  '/' ;
SUB :  '-' ;

MAX : 'max';
MIN : 'min';

EQ  : '==' ;
NEQ : '!=' ;
LT  :  '<' ;
GT  :  '>' ;

LPAR : '(' ;
RPAR : ')' ;

IF  : 'if' ;
THEN:'then';
ELSE:'else';
ENDIF:'endif';



ID  :  [a-zA-Z]+ ;       // match identifiers
INT :  [0-9]+ ;          // match integers
NEWLINE: '\r'? '\n' ;    // return newlines to parser (is end-statement signal)
WS  :  [ \t]+ -> skip ;  // toss out whitespace
