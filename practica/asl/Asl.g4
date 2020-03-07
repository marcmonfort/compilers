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
        : left_expr ASSIGN expr ';'                     # assignStmt
          // if-then-else statement (else is optional)
        | IF expr THEN statements ENDIF                 # ifStmt

        | WHILE expr 'do' statements  ENDWHILE          # whileStmt
          // A function/procedure call has a list of arguments in parenthesis (possibly empty)
        | ident '(' (expr (',' expr)*)? ')' ';'         # procCall

        | RETURN expr? ';'                              # returnStmt    //falta definir en visitFunction(type & symbol) 
          // Read a variable
        | READ left_expr ';'                            # readStmt
          // Write an expression
        | WRITE expr ';'                                # writeExpr
          // Write a string
        | WRITE STRING ';'                              # writeString
        ;
// Grammar for left expressions (l-values in C++)
left_expr
        : ident ('[' expr ']')?         //NEW
        ;

// Grammar for expressions with boolean, relational and aritmetic operators
expr    : op=(SUB|NOT|PLUS) expr                        # symbol           //arithmetic???
        | ident '[' expr ']'                            # array_index
        | ident '(' (expr (',' expr)*)? ')'             # function_call
        | LPAREN expr RPAREN                            # parentesis
        | expr op=(MUL|DIV) expr                        # arithmetic
        | expr op=(PLUS|SUB) expr                       # arithmetic
        | expr op=(EQ|NEQ|GT|GTE|LT|LTE) expr           # relational
        | expr op=(AND|OR) expr                         # logical
        | (INTVAL|FLOATVAL|CHARVAL|BOOLVAL)             # value
        | ident                                         # exprIdent
        ;

ident   : ID
        ;

//////////////////////////////////////////////////
/// Lexer Rules
//////////////////////////////////////////////////

ASSIGN    : '=' ;
//EQUAL     : '==' ;            //OLD maybe problems...

PLUS      : '+' ;
SUB       : '-';
MUL       : '*';
DIV       : '/';

EQ        : '==' ;
NEQ       : '!=' ;
GT        : '>' ;
GTE       : '>=' ;
LT        : '<' ;
LTE       : '<=' ;

AND       : 'and';
OR        : 'or';
NOT       : 'not';


LPAREN      : '(';
RPAREN      : ')';

VAR       : 'var';

INT       : 'int';
BOOL      : 'bool';
FLOAT     : 'float';
CHAR      : 'char';

ARRAY     : 'array' ;

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
