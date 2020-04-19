grammar Expr;
root : statements EOF ;

statements
    : (statement)*
    ;

statement
    : ID ASSIGN expr    # assignStmt
    | WRITE expr        # writeExpr
    | READ ID           # readStmt
    | IF expr THEN statements ENDIF # ifStmt
    | WHILE expr 'do' statements ENDWHILE   # whileStmt
    ; 

expr 
    : '(' expr ')'                      # parenthesis
    | <assoc=right> expr op=POW expr    # arithmetic
    | expr op=(MUL|DIV) expr            # arithmetic
    | expr op=(ADD|SUB) expr            # arithmetic
    | expr op=(EQ|NEQ|LT|LTE|GTE|GT) expr   # relational
    | NUM                               # value
    | ID                                # exprIdent
    ;

MUL : '*' ;
DIV : '/' ;
ADD : '+' ;
SUB : '-' ;
POW : '^' ;

EQ : '=' ;
NEQ : '<>' ;
LT : '<' ;
LTE : '<=' ;
GTE : '>=' ;
GT : '>' ;

ASSIGN : ':=' ;
WRITE : 'write' ;
READ : 'read' ;

IF : 'if' ;
THEN : 'then' ;
ENDIF : 'endif' ;

WHILE : 'while' ;
ENDWHILE : 'endwhile' ;

NUM : [0-9]+ ;
ID  : ('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')* ;


WS : [ \n]+ -> skip ;
