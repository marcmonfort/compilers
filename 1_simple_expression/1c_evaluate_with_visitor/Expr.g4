grammar Expr;

s : e EOF ;

e : e MUL e  // MUL is '*'
  | e ADD e  // ADD is '+'
  | INT
  ;

MUL : '*' ;
ADD : '+' ;
INT : [0-9]+ ;
WS  : [ \t\n]+ -> skip ;
