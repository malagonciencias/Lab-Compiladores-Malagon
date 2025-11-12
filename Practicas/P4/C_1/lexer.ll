%{
#include <sstream>
#include <cstdlib>

#include "Parser.hpp"
#include "Lexer.hpp"

using namespace std;

#undef YY_DECL // Buena práctica
#define YY_DECL int prog::Lexer::lex(prog::Parser::semantic_type *yylval) // Referencia a 1 en Lexer.hpp
%}

%option c++
%option noyywrap
%option outfile="Lexer.cpp"
%option yyclass="Lexer"

DIG [0-9]
LET [a-zA-Z]
ESP [ \t\r\n]+

INT int
FLOAT float
IF if
ELSE else
WHILE while

MAS "+"
MENOS "-"
MULT "*"
DIV "/"
ASIG "="

PYC ";"
COMA ","
LPAR "("
RPAR ")"
LBRAC "{"
RBRAC "}"

NUMERO {DIG}+|{DIG}*"."{DIG}+[eE]{DIG}+|{DIG}+[eE]{DIG}+
ID ({LET}|_)({LET}|{DIG}|_){0,31}

%%

{ESP} {}

{INT} {
	cout << "Se encontró un terminal INT" << endl;
	return Parser::token::INT;
	}

{FLOAT} {
	cout << "Se encontró un terminal FLOAT " << endl;
	return Parser::token::FLOAT;
	}

{IF} {
	cout << "Se encontró un terminal IF" << endl;
	return Parser::token::IF;
	}

{ELSE} {
	cout << "Se encontró un terminal ELSE" << endl;
	return Parser::token::ELSE;
	}

{WHILE} {
	cout << "Se encontró un terminal WHILE" << endl;
	return Parser::token::WHILE;
	}

{MAS} {
	cout << "Se encontró un terminal +" << endl;
	return Parser::token::MAS;
	}

{MENOS} {
	cout << "Se encontró un terminal -" << endl;
	return Parser::token::MENOS;
	}

{MULT} {
	cout << "Se encontró un terminal *" << endl;
	return Parser::token::MULT;
	}

{DIV} {
	cout << "Se encontró un terminal /" << endl;
	return Parser::token::DIV;
	}

{ASIG} {
	cout << "Se encontró un terminal =" << endl;
	return Parser::token::ASIG;
	}

{PYC} {
	cout << "Se encontró un terminal ;" << endl;
	return Parser::token::PYC;
	}

{COMA} {
	cout << "Se encontró un terminal ," << endl;
	return Parser::token::COMA;
	}

{LPAR} {
	cout << "Se encontró un terminal (" << endl;
	return Parser::token::LPAR;
	}

{RPAR} {
	cout << "Se encontró un terminal )" << endl;
	return Parser::token::RPAR;
	}

{LBRAC} {
	cout << "Se encontró un terminal {" << endl;
	return Parser::token::LBRAC;
	}

{RBRAC} {
	cout << "Se encontró un terminal }" << endl;
	return Parser::token::RBRAC;
	}

{NUMERO} {
	cout << "Se encontró un terminal numérico con valor: " << yytext << endl;
    yylval->numero.ival = atof(yytext);
    yylval->numero.tipo = 1; /* 1: Entero, 2: Float */
	return Parser::token::NUM;
	}

{ID} {
	cout << "Se encontró un terminal id con nombre: " << yytext << endl;
    yylval->id = strdup(yytext); // hacemos strdup al pasar la cadena, https://stackoverflow.com/questions/1851829/how-to-use-yylval-with-strings-in-yacc
	return Parser::token::ID;
	}

.	{
	  cout << "Error léxico, TOKEN NO RECONOCIDO: " << yytext <<  "en la línea: " << yylineno << endl;
	}

<<EOF>> {	
         yyterminate();
        }


%%

