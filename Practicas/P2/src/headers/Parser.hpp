#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "Lexer.hpp"
#include "Symbols.hpp"
using namespace std;

namespace C_1
{
  class Parser
  {

  private:
    Lexer *lexer;
    int token;
    
    
  public:
    Parser();
    Parser(Lexer *lexer);
    ~Parser();
    
    void programa(); //función del símbolo incial
    void declaraciones();
    void declaraciones_();
    void declaracion();
    void tipo();
    void lista_var();
    void lista_var_();
    void sentencias();
    void sentencias_();
    void sentencia();
    void expresionS();
    void expresionS_();
    void expresionA();
    void expresionA_();
    void expresionB();
    void expresionB_();
    void expresionC();
    void expresionC_();
    void expresionD();
    
    Token eat();
    void error(string msg);
    void parse();
  };    
    
}


#endif
