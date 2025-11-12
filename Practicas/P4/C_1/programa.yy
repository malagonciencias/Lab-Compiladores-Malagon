%{
#include <iostream>
#include <fstream>
#include <string>
#include <FlexLexer.h>
using namespace std;
%}

%language "C++"
%require "3.2"
%defines "Parser.hpp"
%output "Parser.cpp"
 
%define api.parser.class {Parser}
%define api.namespace {prog}
%define parse.error verbose
%parse-param {Lexer* lexer}

%code requires
{
    namespace prog {
        class Lexer;
    } // namespace prog
} // %code requires
 
%code
{
 #include "Lexer.hpp"
 #define yylex(x) lexer->lex(x) // Referencia a 1 en Lexer.hpp
}

%union {
  struct { //declarado para manejar los tipos de número posibles: 1.- entero, 2.- flotante.
    float ival; //valor 
    int tipo;
  } numero;

    char *id; // nombre del id, no usamos estructura ya que solo es un campo
}

%token<numero> NUM
%token<id> ID // los ids necesitan su token c: 


%left MAS
%left MENOS // En teoria menos puede ser unario con asociatividad derecha, pero...   funciona
%left MULT
%left DIV

%right ASIG // segun https://en.cppreference.com/w/cpp/language/operator_precedence.html

// Caracteres que no tenemos que procesar, realmente no los estamos procesando todavia
%nonassoc PARIZQ
%nonassoc PARDER
%nonassoc INT 
%nonassoc FLOAT 
%nonassoc IF 
%nonassoc ELSE 
%nonassoc WHILE 
%nonassoc PYC // ;
%nonassoc COMA 
%nonassoc LPAR 
%nonassoc RPAR
// Estos dos son nuevos, creo, al menos yo no los tenia (quiza se me olvidaron)
%nonassoc LBRAC // {
%nonassoc RBRAC // }



// %type<numero> expresion

%start programa // simbolo inicial de nuestra gramatica
      

%%

// aca ponemos nuestras producciones

// programa → declaraciones sentencias
programa: declaraciones sentencias { cout << "Análisis léxico y sintáctico terminado. La expresión pertenece a la grámatica" << endl; };

// declaraciones → declaraciones declaracion | declaracion
declaraciones: declaraciones declaracion { cout << "Se leyó una producción: 'declaraciones -> declaraciones declaracion' " << endl; }
             | declaracion { cout << "Se leyó una producción: 'declaraciones -> declaracion' " << endl; };

// declaracion → tipo lista_var ';'
declaracion: tipo lista_var PYC { cout << "Se leyó una producción: 'declaracion -> tipo lista-var' " << endl; };

// tipo → int | float
tipo: INT { cout << "Se leyó una producción: 'tipo -> INT'" << endl; }
    | FLOAT { cout << "Se leyó una producción: 'tipo -> FLOAT'" << endl; };

// lista_var → lista_var ',' identificador | identificador
lista_var: lista_var COMA ID { cout << "Se leyó una producción: 'lista_var -> lista-var, ID'" << endl; }
         | ID { cout << "Se leyó una producción: 'lista_var -> ID'" << endl; };

// sentencias → sentencias sentencia | sentencia
sentencias: sentencias sentencia { cout << "Se leyó una producción: 'SENTENCIAS -> SENTENCIAS SENTENCIA'" << endl; }
          | sentencia { cout << "Se leyó una producción: 'SENTENCIAS -> SENTENCIA'" << endl; };

/* sentencia → identificador = expresion ; | if ( expresion ) { sentencias } else { sentencias } 
             | while ( expresion ) { sentencias }   */
sentencia: ID ASIG expresion PYC { cout << "Se leyó una producción: 'sentencia -> ID = expresion;'" << endl; }
         | IF LPAR expresion RPAR LBRAC sentencias RBRAC ELSE LBRAC sentencias RBRAC { cout << "Se leyó una producción: 'sentencia -> IF ( expresion ) { sentencias } ELSE { sentencias }'" << endl; }
         | WHILE LPAR expresion RPAR LBRAC sentencias RBRAC { cout << "Se leyó una producción: 'sentencia -> WHILE ( expresion ) { sentencias }'" << endl; };

/* expresion → expresion '+' expresion | expresion '-' expresion | expresion '*' expresion 
             | expresion '/' expresión | identificador | numero | '(' expresion ')' */
expresion: expresion MAS expresion { cout << "Se leyó una producción: 'expresion -> expresion + expresion'" << endl; }
         | expresion MENOS expresion { cout << "Se leyó una producción: 'expresion -> expresion - expresion'" << endl; }
         | expresion MULT expresion { cout << "Se leyó una producción: 'expresion -> expresion *expresion'" << endl; }
         | expresion DIV expresion { cout << "Se leyó una producción: 'expresion -> expresion / expresion'" << endl; }
         | ID { cout << "Se encontró un ID: " << *$1 << endl; } 
         | NUM { cout << "Se leyó un número: " << $1.ival << endl; }
         | LPAR expresion RPAR { cout << "Se leyó una producción: 'expresion -> ( expresion )'" << endl; }
         // debido a como manejamos los negativos, tenemos que añadir esta regla
         | MENOS expresion { cout << "Se leyó una producción: 'expresion -> -expresion'" << endl; };

%%

void prog::Parser::error(const std::string& msg) {
    std::cerr << "Error en la línea: " << lexer->lineno() << ": " << msg << std::endl;
}


#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char *argv[]){
    if(argc < 2){
        cout<<"Faltan argumentos "<<endl;
        return EXIT_FAILURE;
    }
    filebuf fb;
    fb.open(string(argv[1]), ios::in);
    istream in(&fb);
    prog::Lexer lexer(&in);
    prog::Parser parser(&lexer);
    parser.parse();
    fb.close();
    return 0;
    /*
    prog::Lexer scanner{ std::cin, std::cerr };
    prog::Parser parser{ &scanner };
    //std::cout.precision(10);
    parser.parse();*/
}
