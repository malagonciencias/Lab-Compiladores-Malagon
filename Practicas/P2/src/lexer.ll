%{
#include <iostream>
#include <string>
using namespace std;

#include "headers/Symbols.hpp"
#include "headers/Lexer.hpp"

int line=1;
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="Lexer"

DIG [0-9]
LET [a-zA-Z]
ESP [ \t\r]
NLINE \n

INT int
FLOAT float
IF if
ELSE else
WHILE while

MAS "+"
MENOS "-"
POR "*"
DIV "/"
ASIG "="

PYC ";"
COMA ","
LPAR "("
RPAR ")"

NUMERO {DIG}+|{DIG}*"."{DIG}+[eE]{DIG}+|{DIG}+[eE]{DIG}+
ID ({LET}|_)({LET}|{DIG}|_){0,31}

%%

{ESP} {}
{NLINE} {line++;}
{INT} { return t_int;}
{FLOAT} { return t_float;}
{IF} { return t_if;}
{ELSE} { return t_else;}
{WHILE} { return t_while;}
{MAS} { return t_mas; }
{MENOS} { return t_menos;}
{POR} { return t_por;}
{DIV} { return t_div;}
{ASIG} { return t_asig;}
{PYC} { return t_pyc;}
{COMA} { return t_coma;}
{LPAR} { return t_lpar;}
{RPAR} { return t_rpar;}
{NUMERO} { return t_numero;}
{ID} { return t_id;}
. { cout << "ERROR LEXICO " << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}

int Lexer::getLine()
{
    return line;
}
