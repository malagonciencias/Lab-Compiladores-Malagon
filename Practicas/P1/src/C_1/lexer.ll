%{
#include <iostream>
#include <string>
using namespace std;

#include "tokens.hpp"
#include "Lexer.hpp"

%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="C_1::Lexer"
%option case-insensitive


DIG [0-9]
LET [a-zA-Z]
ESP [ \t\n]

INT int
FLOAT float
IF if
ELSE else
WHILE while

MAS "+"
MENOS "-"
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
{INT} { cout << "12, " << yytext << endl;}
{FLOAT} { cout << "15, " << yytext << endl;}
{IF} { cout << "11, " << yytext << endl;}
{ELSE} { cout << "14, " << yytext << endl;}
{WHILE} { cout << "13, " << yytext << endl;}
{MAS} { cout << "1, " << yytext << endl;}
{MENOS} { cout << "2, " << yytext << endl;}
{DIV} { cout << "4, " << yytext << endl;}
{ASIG} { cout << "5, " << yytext << endl;}
{PYC} { cout << "9, " << yytext << endl;}
{COMA} { cout << "8, " << yytext << endl;}
{LPAR} { cout << "6, " << yytext << endl;}
{RPAR} { cout << "7, " << yytext << endl;}
{NUMERO} { cout << "16, " << yytext << endl;}
{ID} { cout << "10, " << yytext << endl;}
.   { cout << "ERROR LEXICO, " << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}

