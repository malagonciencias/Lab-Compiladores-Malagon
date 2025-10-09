#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** 
 * 1. Definir en un comentario la gramática G(N, T, P, S)
 *
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
    strEmpty,
    programa, 
    declaraciones,
    declaraciones_,
    declaracion,
    tipo,
    lista_var,
    lista_var_,
    sentencias,
    sentencias_,
    sentencia, 
    expresionS,
    expresionS_,
    expresionA,
    expresionA_, 
    expresionB,
    expresionB_,
    expresionC,
    expresionC_,
    expresionD
};

#endif // !__SYMBOLS_HPP__
