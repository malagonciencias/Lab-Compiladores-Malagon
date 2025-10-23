#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** 
 * 1. Definir en un comentario la gramática G'(N', T, P', S)
 * N = { programa, declaraciones, declaracion, tipo, lista_var, sentencias, sentencia, expresion}
 * T = {int, float, identificador, ";", if, else, "(", ")", while, "=", ",", numero}
 * S = { programa }
 * P = {
 *  programa → declaraciones sentencias
 *  declaraciones → declaracion declaraciones'
 *  declaraciones → declaracion declaraciones'declaraciones → declaracion declaraciones'
 *  declaracion → tipo lista_var 
 *  tipo → int | float
 *  lista_var → identificador lista_var'
 *  lista_var' → "," identificador lista_var' ∣ ϵ
 *  sentencias → sentencia sentencias'
 *  sentencias' → sentencia sentencias' ∣ ϵ
 *  sentencia → identificador = expresionS ; ∣ if ( expresionS ) sentencias else sentencias ∣ while ( expresionS ) sentencias
 *  expresionS → expresionA expresionS'
 *  expresionS' → + expresionA expresionS' ∣ ϵ
 *  expresionA → expresionB expresionA'
 *  expresionA' → - expresionB expresionA' ∣ ϵ
 *  expresionB → expresionC expresionB'
 *  expresionB' → * expresionC expresionB' ∣ ϵ
 *  expresionC → expresionD expresionC'
 *  expresionC' → / expresionD expresionC' ∣ ϵ
 *  expresionD → ( expresionS ) ∣ identificador ∣ numero
 * }
 */


/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { 
    t_eof, // 0
    t_mas, // 1 
    t_menos, // 2
    t_por, //3
    t_div, // 4 
    t_asig, // 5
    t_lpar, // 6
    t_rpar, // 7
    t_coma, // 8
    t_pyc, // 9
    t_id, // 10
    t_if, // 11
    t_int, // 12
    t_while, // 13
    t_else, // 14
    t_float, // 15
    t_numero // 16
};

/**
 * 3. Determinar la enumeración para el conjunto N
 */
enum NoTerm { 
    strEmpty, // 0 
    programa, // 1
    declaraciones, // 2
    declaraciones_, // 3
    declaracion, // 4
    tipo, // 5
    lista_var, // 6
    lista_var_, // 7
    sentencias, // 8
    sentencias_, // 9
    sentencia, // 10
    expresionS, // 11
    expresionS_, // 12
    expresionA, // 13
    expresionA_, // 14
    expresionB, // 15
    expresionB_, // 16
    expresionC, // 17
    expresionC_, // 18
    expresionD // 19
};

#endif // !__SYMBOLS_HPP__
