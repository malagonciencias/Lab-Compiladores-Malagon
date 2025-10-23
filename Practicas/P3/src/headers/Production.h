#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <vector>
using namespace std;
#include "Symbol.h"

/**
 * Clase para representar una producción
 */
class Production
{
private:
  Symbol head; //identificador del símbolo del encabezado de la producción (syms)
  vector<Symbol> body; //arreglo de enteros para representar el cuerpo de la producción (syms)
  
public:
  Production(/* args */); //constructor por omisión
  Production(Symbol head, vector<Symbol> body); //constructor con encabezado y cuerpo 
  ~Production(); //destructor
  
  Symbol getHead(); //obtener encabezado de la producción
  vector<Symbol> getBody(); //obtener cuerpo de la producción
};
#endif // PRODUCTION_H
