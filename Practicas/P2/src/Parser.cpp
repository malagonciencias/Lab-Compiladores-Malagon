#include "headers/Parser.hpp"
#include <iostream>

namespace C_1
{
  Parser::Parser(/* args */)
  {
  }

  Parser::Parser(Lexer *lexer)
  {
    this->lexer = lexer;
  }
    
  Parser::~Parser()
  {
  }

  // programa -> declaraciones sentencias
  void Parser::programa(){
    declaraciones();
    sentencias();
  }

  // declaraciones -> declaracion declaraciones'
  void Parser::declaraciones(){
    declaracion();
    declaraciones_();
  }

  // declaraciones' -> declaracion declaraciones' | epsilon
  void Parser::declaraciones_(){
    // produccion epsilon con recursividad, tomamos el first(declaracion) como token a leer para entrar en la secuencia
    while(token == t_int || token == t_float){
      // una vez entramos en la produccion seguimos las reglas tal cual
      declaracion();
    }
  }

  // declaracion -> tipo lista_var
  void Parser::declaracion(){
    tipo();
    lista_var();
    if(token == t_pyc)
      token = eat();
    else 
      error("se esperaba un ';'");
  }

  // tipo -> int | float
  void Parser::tipo(){
    // se espera terminal, token debe ser el correcto
    if(token == t_int || token == t_float)
      // terminal, comemos token
      token = eat();
    else
      // de lo contrario nos encontramos un error
      error("los tipos válidos son 'int' o 'float'");
  }

  // lista_var -> identificador lista_var'
  void Parser::lista_var(){
    // nuevamente nos encontramos con un terminal, comemos y aseguramos que el token sea el esperado
    if(token == t_id){
      token = eat();
      lista_var_();
    } else 
      // de lo contrario nos encontramos un error
      error("se esperaba un ID");
  }

  // lista_var' -> "," identificador lista_var' | epsilon
  void Parser::lista_var_(){
    // produccion epsilon recursiva, se toma el while del first 
    while(token == t_coma){
      // terminal, comemos token
      token = eat();
      // nuevamente nos encontramos un terminal, aseguramos que encaje con lo esperado
      if(token == t_id)
        // terminal, comemos
        token = eat();
      else 
        error("la coma debe ser seguida por un ID");
    }
  }

  // sentencias -> sentencia sentencias'
  void Parser::sentencias(){
    sentencia();
    sentencias_();
  }

  // sentencias' -> sentencia sentencias' | epsilon
  void Parser::sentencias_(){
    // funcion epsilon recursiva, buscamos first(sentencia) para entrar en la secuencia
    while(token == t_id || token == t_if || token == t_while){
      sentencia();
    }
  }

  // sentencia -> identificador "=" expresionS ";" 
  // | "if" "(" expresionS ")" sentencias "else" sentencias
  // | "while" "(" expresionS ")" sentencias
  void Parser::sentencia(){
    // Tenemos 3 "caminos", haremos un switch para cada camino
    switch(token) {
      case t_id:
        // encontramos un terminal, comemos token
        token = eat();
        // tenemos que recibir un terminal nuevamente
        if(token == t_asig)
          // comemos token
          token = eat();
        else 
          // levantamos error si no se recibe terminal esperado
          error("se esperaba un '='");
        // seguimos independientemente de errores
        expresionS();
        if(token == t_pyc)
          // comemos token 
          token = eat();
        else 
          // levantamos error
          error("se espearaba un ';'");
        break;

      case t_if:
        // encontramos un terminal, comemos token
        token = eat();
        // tenemos que recibir un terminal nuevamente
        if(token == t_lpar)
          // comemos token
          token = eat();
        else 
          // levantamos error si no se recibe terminal esperado
          error("se esperaba un '('");
        // seguimos independientemente de errores
        expresionS();
        if(token == t_rpar)
          // comemos token 
          token = eat();
        else 
          // levantamos error
          error("se espearaba un ')'");
        // seguimos a pesar de errores
        sentencias();
        if(token == t_else)
          // comemos token 
          token = eat();
        else 
          // levantamos error
          error("se espearaba un 'else'");
        // seguimos a pesar de errores
        sentencias();
        break;

      case t_while:
         // encontramos un terminal, comemos token
        token = eat();
        // tenemos que recibir un terminal nuevamente
        if(token == t_lpar)
          // comemos token
          token = eat();
        else 
          // levantamos error si no se recibe terminal esperado
          error("se esperaba un '('");
        // seguimos independientemente de errores
        expresionS();
        if(token == t_rpar)
          // comemos token 
          token = eat();
        else 
          // levantamos error
          error("se espearaba un ')'");
        // seguimos a pesar de errores
        sentencias();
        break;

      default:
        error("se esperaba un identificador o un if o un while");
        break;
    }
  }

  // expresionS -> expresionA expresionS'
  void Parser::expresionS(){
    expresionA();
    expresionS_();
  }

  // expresionS' -> "+" expresionA expresionS' | epsilon
  void Parser::expresionS_(){
    // produccion epsilon recursiva
    while(token == t_mas){
      // se encontro terminal, comemos
      token = eat();
      expresionA();
      // expresionS_();
    }
  }

  // expresionA -> expresionB expresionA'
  void Parser::expresionA(){
    expresionB();
    expresionA_();
  }

  // expresionA -> "-" expresionB expresionA' | epsilon
  void Parser::expresionA_(){
    // produccion epsilon recursiva
    while(token == t_menos){
      // se encontro terminal, comemos
      token = eat();
      expresionB();
      // expresionA_();
    }
  }

  // expresionB -> expresionC expresionB'
  void Parser::expresionB(){
    expresionC();
    expresionB_();
  }

  // expresionB -> "*" expresionC expresionB' | epsilon
  void Parser::expresionB_(){
    // produccion epsilon recursiva
    while(token == t_por){
      // se encontro terminal, comemos
      token = eat();
      expresionC();
      // expresionB_();
    }
  }

  // expresionC -> expresionD expresionC'
  void Parser::expresionC(){
    expresionD();
    expresionC_();
  }

  // expresionC -> "/" expresionD expresionC' | epsilon
  void Parser::expresionC_(){
    // produccion epsilon recursiva
    while(token == t_div){
      // se encontro terminal, comemos
      token = eat();
      expresionD();
      // expresionC_();
    }
  }

  // expresionD -> "(" expresionS ")" | identificador | numero
  void Parser::expresionD(){
    // Nuevamente tenemos muchos or, lo haremos con un switch 
    switch(token) {
      case t_lpar:
        // terminal, comemos token
        token = eat();
        expresionS();
        if(token == t_rpar)
          // terminal, comemos token
          token = eat();
        else 
          error("se esperaba un ')'");
        break;
      case t_id: case t_numero:
        // en estos casos simplemente comemos 
        token = eat();
        break;
      default:
        error("se esperaba '(' o un identificador o un numero");
        break;
    }
  }

  /************************************************************************/
  /**                                                                    **/
  /**                       Funciones por cada NT                        **/
  /**                                                                    **/
  /************************************************************************/


  Token Parser::eat(){
    return (Token) lexer->yylex();
  }

  void Parser::error(string msg){
    cout << "ERROR DE SINTAXIS " << msg << " en la línea "<< lexer->getLine() <<endl;
  }   

  void Parser::parse(){
    token = eat();
    programa();
    if(token == t_eof)
      cout << "La cadena es aceptada" << endl;
    else 
      cout << "La cadena no pertenece al lenguaje generado por la gramática" << endl;
  }

}
