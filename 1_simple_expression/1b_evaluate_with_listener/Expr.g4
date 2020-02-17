grammar Expr;

s : e EOF ; //EOF hace que "1 + 2 34 -" salga error y no lo ignore"

e : SUB e
  | e (MUL|DIV) e  // MUL is '*'
  | e (ADD|SUB) e  // ADD is '+'
  | MAX '(' e ',' e ')'
  | MIN '(' e ',' e ')'
  | LPAR e RPAR
  | INT
  ;

MUL : '*' ; //se pone como token
DIV : '/' ;
ADD : '+' ;
SUB : '-' ;
MAX : 'max';  
MIN : 'min';
// NEG : '-'; mal, igual que sub
LPAR : '(' ;
RPAR : ')' ;



INT : [0-9]+ ;
WS  : [ \t\n]+ -> skip ;
