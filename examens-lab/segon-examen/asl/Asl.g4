//////////////////////////////////////////////////////////////////////
//
//    Asl - Another simple language (grammar)
//
//    Copyright (C) 2017  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

grammar Asl;

//////////////////////////////////////////////////
/// Parser Rules
//////////////////////////////////////////////////

// A program is a list of functions
program : function+ EOF
        ;

// A function has a name, a list of parameters and a list of statements
function
        : FUNC ID '(' parameters ')' (':' basic_type)? declarations statements ENDFUNC          //return type???
        ;
        
parameters
        : (|ID ':' type (',' ID ':' type)*)     //si esta en interrogante arriba falla al hacer visit de funcion sin parametros
        ; 

declarations
        : (variable_decl)*
        ;

variable_decl
        : VAR ID (','ID)* ':' type
        ;

type
        : basic_type
        | array_type
        ;

array_type
        : ARRAY '[' INTVAL ']' 'of' basic_type
        ;


basic_type    
        : INT
        | FLOAT
        | BOOL
        | CHAR
        ;


statements
        : (statement)*
        ;

// The different types of instructions
statement
          // Assignment
        : left_expr ASSIGN expr ';'                                     # assignStmt
          // if-then-else statement (else is optional)
        | FOR expr IN RANGE '(' (expr (',' expr)*)? ')' 'do' statements ENDFOR  # forRange  //exam 2020
        
        | IF expr THEN statements (ELSE statements)? ENDIF              # ifStmt

        | WHILE expr 'do' statements  ENDWHILE                          # whileStmt
          // A function/procedure call has a list of arguments in parenthesis (possibly empty)
        | ident '(' (expr (',' expr)*)? ')' ';'                         # procCall

        | RETURN expr? ';'                                              # returnStmt 
          // Read a variable
        | READ left_expr ';'                                            # readStmt
          // Write an expression
        | WRITE expr ';'                                                # writeExpr
          // Write a string
        | WRITE STRING ';'                                              # writeString
        ;
        
// Grammar for left expressions (l-values in C++)
left_expr
        : ident ('[' expr ']')? 
        ;

// Grammar for expressions with boolean, relational and aritmetic operators
expr    
        : '(' expr ')'                                  # parenthesis
        | op=FILTER expr INTO expr USING expr              # filter
        | expr op=A_MAX                                 # arrayMax //exam 2019
        | op=MAX '('(expr (',' expr)*)? ')'             # max //exam2020
        | op=SUM '('((expr (',' expr)*)?)? ')'             # sum //exam2020
        | ident '[' expr ']'                            # array_index
        | ident '(' (expr (',' expr)*)? ')'             # function_call
        | op=(NOT|PLUS|SUB) expr                        # unary
        | expr op=(MUL|DIV|MOD) expr                    # arithmetic
        | expr op=(PLUS|SUB) expr                       # arithmetic
        | expr op=(EQ|NEQ|GT|GTE|LTE|LT) expr           # relational
        | expr op=AND expr                              # logical
        | expr op=OR expr                               # logical
        | (INTVAL|FLOATVAL|BOOLVAL|CHARVAL)             # value
        | ident                                         # exprIdent
        ;

ident   : ID
        ;

//////////////////////////////////////////////////
/// Lexer Rules
//////////////////////////////////////////////////

ASSIGN    : '=' ;

// ---  Arithmetic  ---
PLUS      : '+' ;
SUB       : '-';
MUL       : '*';
DIV       : '/';
MOD       : '%';

// ---  Relational  ---
EQ        : '==' ;
NEQ       : '!=' ;
GT        : '>' ;
GTE       : '>=' ;
LT        : '<' ;
LTE       : '<=' ;

// ---  Logical  ---
AND       : 'and';
OR        : 'or';
NOT       : 'not';

// ---  Types  ---     
VAR       : 'var';
INT       : 'int';
FLOAT     : 'float';
BOOL      : 'bool';
CHAR      : 'char';
ARRAY     : 'array' ;

// ---  Constructs  ---
IF        : 'if' ;
THEN      : 'then' ;
ELSE      : 'else' ;
ENDIF     : 'endif' ;

WHILE     : 'while' ;
ENDWHILE  : 'endwhile';

FUNC      : 'func' ;
ENDFUNC   : 'endfunc' ;
RETURN    : 'return' ;

READ      : 'read' ;
WRITE     : 'write' ;


//vigilar que las variables no tengan el mismo nombre
// --- Exam 2020 - final  ---
SUM       : 'sum' ;

FILTER    : 'filter' ;
INTO      : 'into' ;
USING     : 'using' ;


// --- Exam 2020  ---
MAX       : 'max_';

FOR       : 'for';
IN        : 'in';
RANGE     : 'range';
ENDFOR    : 'endfor';

// --- Exam 2019  ---
A_MAX       : '.max';

// --- Values  ---
INTVAL    : ('0'..'9')+ ;
FLOATVAL  : ('0'..'9')+ '.' ('0'..'9')+ ;
CHARVAL   : '\'' ( ESC_SEQ | ~('\\'|'\'')) '\'' ;
BOOLVAL   : 'true'|'false';

ID        : ('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')* ;   //hay que poner debajo de todos los nombres, para que esos tengan prioridad.


// Strings (in quotes) with escape sequences
STRING    : '"' ( ESC_SEQ | ~('\\'|'"') )* '"' ;

fragment
ESC_SEQ   : '\\' ('b'|'t'|'n'|'f'|'r'|'"'|'\''|'\\') ;

// Comments (inline C++-style)
COMMENT   : '//' ~('\n'|'\r')* '\r'? '\n' -> skip ;

// White spaces
WS        : (' '|'\t'|'\r'|'\n')+ -> skip ;
// Alternative description
// WS        : [ \t\r\n]+ -> skip ;


/* LPAREN      : '(';
RPAREN      : ')'; */