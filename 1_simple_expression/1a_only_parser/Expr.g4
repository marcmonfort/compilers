grammar Expr;

s : e ;

e : e ('*'|'/') e
  | e ('+'|'-') e //misma prioridad
  | '-' e
  | MAX '(' e ',' e ')'
  | MIN '(' e ',' e ')'
  | INT
  ;

MAX : 'max';  //creamos token (mejor asi)
MIN : 'min';
INT : [0-9]+ ;
WS  : [ \t\n]+ -> skip ;
