#include "headers/ParserLL.hpp"


ParserLL::ParserLL(Lexer *lexer)
{
    this->lexer = lexer;
}

ParserLL::~ParserLL()
{
}


void ParserLL::loadSyms()
{
  /*********************************************
   * 4. Agregar todos los símbolos (N'∪T) de G'*
   *********************************************/

  //  No terminales
  grammar.addSymbol(strEmpty, Symbol(strEmpty));
  grammar.addSymbol(programa, Symbol(programa));
  grammar.addSymbol(declaraciones, Symbol(declaraciones));
  grammar.addSymbol(declaraciones_, Symbol(declaraciones_));
  grammar.addSymbol(declaracion, Symbol(declaracion));
  grammar.addSymbol(tipo, Symbol(tipo));
  grammar.addSymbol(lista_var, Symbol(lista_var));
  grammar.addSymbol(lista_var_, Symbol(lista_var_));
  grammar.addSymbol(sentencias, Symbol(sentencias));
  grammar.addSymbol(sentencias_, Symbol(sentencias_));
  grammar.addSymbol(sentencia, Symbol(sentencia));
  grammar.addSymbol(expresionS, Symbol(expresionS));
  grammar.addSymbol(expresionS_, Symbol(expresionS_));
  grammar.addSymbol(expresionA, Symbol(expresionA));
  grammar.addSymbol(expresionA_, Symbol(expresionA_));
  grammar.addSymbol(expresionB, Symbol(expresionB));
  grammar.addSymbol(expresionB_, Symbol(expresionB_));
  grammar.addSymbol(expresionC, Symbol(expresionC));
  grammar.addSymbol(expresionC_, Symbol(expresionC_));
  grammar.addSymbol(expresionD, Symbol(expresionD));

  // Terminales

  grammar.addSymbol(t_eof, Symbol(t_eof));
  grammar.addSymbol(t_mas, Symbol(t_mas));
  grammar.addSymbol(t_menos, Symbol(t_menos));
  grammar.addSymbol(t_por, Symbol(t_por));
  grammar.addSymbol(t_div, Symbol(t_div));
  grammar.addSymbol(t_asig, Symbol(t_asig));
  grammar.addSymbol(t_lpar, Symbol(t_lpar));
  grammar.addSymbol(t_rpar, Symbol(t_rpar));
  grammar.addSymbol(t_coma, Symbol(t_coma));
  grammar.addSymbol(t_pyc, Symbol(t_pyc));
  grammar.addSymbol(t_id, Symbol(t_id));
  grammar.addSymbol(t_if, Symbol(t_if));
  grammar.addSymbol(t_int, Symbol(t_int));
  grammar.addSymbol(t_while, Symbol(t_while));
  grammar.addSymbol(t_else, Symbol(t_else));
  grammar.addSymbol(t_float, Symbol(t_float));
  grammar.addSymbol(t_numero, Symbol(t_numero));

  // Indicamos el numero de terminales y no terminales
  grammar.setNum(17, 19);

}

void ParserLL::loadProds()
{
  /************************************************
   * 5. Agregar todas las producciones (P') de G' *
   ************************************************/  
    
  //  programa → declaraciones sentencias
  grammar.addProd(1, Production(programa, {declaraciones, sentencias}));

  //  declaraciones → declaracion declaraciones'
  grammar.addProd(2, Production(declaraciones, {declaracion, declaraciones_}));

  //  declaraciones → declaracion declaraciones'
  grammar.addProd(3, Production(declaraciones_, {declaracion, declaraciones_}));
  //  Produccion epsilon
  grammar.addProd(4, Production(declaraciones_, {strEmpty}));

  //  declaracion → tipo lista_var 
  grammar.addProd(5, Production(declaracion, {tipo, lista_var}));

  //  tipo → int | float
  grammar.addProd(6, Production(tipo, {t_int}));
  grammar.addProd(7, Production(tipo, {t_float}));

  //  lista_var → identificador lista_var'
  grammar.addProd(8, Production(lista_var, {t_id, lista_var_}));

  //  lista_var' → "," identificador lista_var' ∣ ϵ
  grammar.addProd(9, Production(lista_var_, {t_coma, t_id, lista_var_}));
  //  Produccion epsilon
  grammar.addProd(10, Production(lista_var_, {strEmpty}));

  //  sentencias → sentencia sentencias'
  grammar.addProd(11, Production(sentencias, {sentencia, sentencias_}));

  //  sentencias' → sentencia sentencias' ∣ ϵ
  grammar.addProd(12, Production(sentencias_, {sentencia, sentencias_}));
  //  Produccion epsilon
  grammar.addProd(13, Production(sentencias_, {strEmpty}));

  //  sentencia → identificador = expresionS ; ∣ if ( expresionS ) sentencias else sentencias ∣ while ( expresionS ) sentencias
   
  grammar.addProd(14, Production(sentencia, {t_id, t_asig, expresionS}));
  grammar.addProd(15, Production(sentencia, {t_if, t_lpar, expresionS, t_rpar, sentencias, t_if, sentencias}));
  grammar.addProd(16, Production(sentencia, {t_while, t_lpar, expresionS, t_rpar, sentencias}));

  //  expresionS → expresionA expresionS'
  grammar.addProd(17, Production(expresionS, {expresionA, expresionS_}));

  //  expresionS' → + expresionA expresionS' ∣ ϵ
  grammar.addProd(18, Production(expresionS_, {t_mas, expresionA, expresionS_}));
  //  Produccion epsilon
  grammar.addProd(19, Production(expresionS_, {strEmpty}));

  //  expresionA → expresionB expresionA'
  grammar.addProd(20, Production(expresionA, {expresionB, expresionA_}));

  //  expresionA' → - expresionB expresionA' ∣ ϵ
  grammar.addProd(21, Production(expresionA_, {t_menos, expresionB, expresionA_}));
  //  Produccion epsilon
  grammar.addProd(22, Production(expresionA_, {strEmpty}));

  //  expresionB → expresionC expresionB'
  grammar.addProd(23, Production(expresionB, {expresionC, expresionB_}));

  //  expresionB' → * expresionC expresionB' ∣ ϵ
  grammar.addProd(24, Production(expresionB_, {t_por, expresionC, expresionB_}));
  //  Produccion epsilon
  grammar.addProd(25, Production(expresionB_, {strEmpty}));

  //  expresionC → expresionD expresionC'
  grammar.addProd(26, Production(expresionC, {expresionD, expresionC_}));

  //  expresionC' → / expresionD expresionC' ∣ ϵ
  grammar.addProd(27, Production(expresionC_, {t_div, expresionD, expresionC_}));
  //  Produccion epsilon
  grammar.addProd(28, Production(expresionC_, {strEmpty}));

  //  expresionD → ( expresionS ) ∣ identificador ∣ numero
   grammar.addProd(29, Production(expresionD, {t_lpar, expresionS, t_rpar}));
   grammar.addProd(30, Production(expresionD, {t_id}));
   grammar.addProd(31, Production(expresionD, {t_numero}));
}

void ParserLL::loadTable()
{

  /*************************************************
   **     6.Cargar la tabla de AS predictivo      **
   *************************************************/
  
  //  Llenamos la tabla de acuerdo a como aparece en el readme
  table[programa][t_int] = 1;
  table[programa][t_float] = 1;

  table[declaraciones][t_int] = 2;
  table[declaraciones][t_float] = 2;

  table[declaraciones_][t_int] = 3;
  table[declaraciones_][t_float] = 3;

  table[declaraciones_][t_id] = 4;
  table[declaraciones_][t_if] = 4;
  table[declaraciones_][t_while] = 4;

  table[declaracion][t_int] = 5;
  table[declaracion][t_float] = 5;

  table[tipo][t_int] = 6;

  table[tipo][t_float] = 7;

  table[lista_var][t_id] = 8;

  table[lista_var_][t_coma] = 9;

  table[lista_var_][t_pyc] = 10;

  table[sentencias][t_id] = 11;
  table[sentencias][t_if] = 11;
  table[sentencias][t_while] = 11;

  table[sentencias_][t_id] = 12;
  table[sentencias_][t_if] = 12;
  table[sentencias_][t_while] = 12;

  table[sentencias_][t_else] = 13;
  table[sentencias_][t_eof] = 13;

  table[sentencia][t_id] = 14;
  table[sentencia][t_if] = 15;
  table[sentencia][t_while] = 16;

  table[expresionS][t_id] = 17;
  table[expresionS][t_lpar] = 17;
  table[expresionS][t_numero] = 17;

  table[expresionS_][t_mas] = 18;
  table[expresionS_][t_pyc] = 19;
  table[expresionS_][t_rpar] = 19;

  table[expresionA][t_id] = 20;
  table[expresionA][t_lpar] = 20;
  table[expresionA][t_numero] = 20;

  table[expresionA_][t_menos] = 21;
  table[expresionA_][t_pyc] = 22;
  table[expresionA_][t_rpar] = 22;
  table[expresionA_][t_mas] = 22;

  table[expresionB][t_id] = 23;
  table[expresionB][t_lpar] = 23;
  table[expresionB][t_numero] = 23;

  table[expresionB_][t_por] = 24;
  table[expresionB_][t_menos] = 25;
  table[expresionB_][t_mas] = 25;
  table[expresionB_][t_pyc] = 25;
  table[expresionB_][t_rpar] = 25;
  
  table[expresionC][t_id] = 26;
  table[expresionC][t_lpar] = 26;
  table[expresionC][t_numero] = 26;

  table[expresionC_][t_div] = 27;
  table[expresionC_][t_menos] = 28;
  table[expresionC_][t_mas] = 28;
  table[expresionC_][t_pyc] = 28;
  table[expresionC_][t_rpar] = 28;
  table[expresionC_][t_por] = 28;

  table[expresionD][t_lpar] = 29;
  table[expresionD][t_id] = 30;
  table[expresionD][t_numero] = 31;

}

int ParserLL::parse()
{
  /**************************************************
   ** 7. Implementar el algoritmo de AS predictivo **
   **************************************************/

  //Auxiliares
  stack<Symbol> pila;    
  map<Token, int>::iterator accion;    
  vector<int> body;    
  Symbol X;
  this->loadSyms();
  this->loadProds();
  this->loadTable();

  // Añadimos el fin de archivo a la pila
  pila.push(Symbol(t_eof));
  pila.push(Symbol(programa)); // Metemos la produccion inicial de la gramatica
  token = eat(); // Comemos un token antes de empezar
  // Realmente no hace mucha diferencia si iteramos así o mientras el token no sea eof
  while(!pila.empty()) {
    X = pila.top();
    if(X.getType() == terminal){ // el token es terminal
      if(X.getToken() == token){ // si X == p
        pila.pop(); // Quitamos uno de la pila
        token = eat(); // Avanzamos al siguiente token
      }else {
        error("Se esperaba el token " + std::to_string(token)); 
        return -1;
      }
    } else { // Para los no terminales
      // Verificamos en la tabla de analisis sintactico
      // Iteramos sobre la fila de la tabla con la el encabeza X
      auto itFila = table.find(X.getNoTerm());
      if(itFila != table.end()) {
        // Buscamos las columnas hasta encontrar el token actual
        auto itColum = itFila->second.find(token);
        if(itColum != itFila->second.end()) { // Encontramos la produccion en la tabla
          int numeroProduccion = itColum->second;
          pila.pop();
          Production prod = grammar.getProd(numeroProduccion); // obtenemos el numero de produccion que definimos
          vector<int> cuerpoProd = prod.getBody();
          // Iteramos de manera reversa sobre la produccion
          for(auto revIt = cuerpoProd.rbegin(); revIt != cuerpoProd.rend(); revIt++){
            Symbol prodSym = grammar.getSym(*revIt);
            if(!(prodSym.getType() == terminal && prodSym.getNoTerm() == strEmpty)) // Ignoramos producciones epsilon
              pila.push(prodSym);
          }
        } else { // No se encontró el terminal en la fila
          error("El token '" + std::to_string(token) + "' no está considerado en esta producción, o quizá en ninguna");
          return -1;
        }
      } else { // No se encontró en la columna de no terminales
        error("El no terminal '" + std::to_string((X.getNoTerm())) + "' no está considerado en la grámatica");
        return -1;
      }
      

    }
  }
  if(token == t_eof) {
    aceptar("Cadena aceptada");
    return 0;
  } else {
    error("La cadena no está bien formada");
    return -1;
  }
}

void ParserLL::error(string msg)
{
    cout<<msg<<endl;
    exit(EXIT_FAILURE);
}

Token ParserLL::eat()
{
    return (Token) lexer->yylex();    
}

void ParserLL::aceptar(string msg)
{
    cout<<msg<<endl;
}
