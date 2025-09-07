#include  <iostream>
#include <fstream>
#include "Lexer.hpp"

using namespace std;
using namespace C_1;


int main(int argc, char *argv[]) {
  
    // Se verifica que sea dado un archivo de prueba para lectura
    if(argc < 2){
        cout << "Faltan argumentos" << endl;
        return EXIT_FAILURE;
    }

    // Buffer de caracteres
    filebuf fb;
    // Se abre el archivo con el nombre dado en los argumentos
    fb.open(string(argv[1]), ios::in);
    // Se declara un torrente de input de donde sacaremos los token
    istream in(&fb);
    // Leemos los caracteres del input stream
    Lexer lexer(&in);
    // Se lee hasta que se identifique un token definido
    int token = lexer.yylex();

    // Mientras haya tokens que leer
    while(token != 0){
        // Imprimimos el valor dado por lexer.ll
        cout << token << ", " << lexer.YYText() << endl;
        token = lexer.yylex();
    }
    
    fb.close();    
    return 0;
}
