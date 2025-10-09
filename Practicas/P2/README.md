# [Compiladores 2026-1] Grupo 7010
## Práctica 2 Repositorio base


### Estructura del directorio
```c++
p3
├── README.md
└── src //carpeta de código
    ├── headers
    │   ├── Lexer.hpp   //header de la clase Lexer
    │   ├── Parser.hpp  //header de la clase Parser
    │   └── Symbols.hpp //definición de símbolos
    ├── lexer.ll        //definición del an. léxico
    ├── main.cpp        //contiene la función principal del programa
    ├── Makefile        //boceto de Makefile (no funciona aún)
    ├── Parser.cpp      //código fuente de la clase Parser
    └── prueba          ////archivo de entrada para el analizador (léxico y sintáctico)
```

### Uso

#### Compilación

```bash
$ cd src/
$ flex++ lexer.ll
$ g++ Lexer.cpp Parser.cpp main.cpp -o analyzer
```

#### Ejecución

```bash
$ ./analyzer prueba
```

#### Ejercicios
Para la gramática G = ( N, Σ, P, S), descrita por las siguientes producciones: 
> P = {
>> programa → declaraciones sentencias <br>
>> declaraciones → declaraciones declaracion | declaracion <br>
>> declaracion → tipo lista_var **;** <br>
>> tipo → **int** | **float** <br>
>> lista_var → lista_var **,** _**identificador**_ | _**identificador**_ <br>
>> sentencias → sentencias sentencia | sentencia <br>
>> sentencia → _**identificador**_ **=** expresion **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>> expresion → expresion **+** expresion | expresion **-** expresion | expresion __\*__ expresion | expresion **\/** expresión | _**identificador**_ | **_numero_** <br>
>> expresion → **(** expresion **)** <br>
}


1. Determinar en un archivo Readme, en formato Markdown (.md) o LaTeX (.tex) -- con su respectivo PDF, para este último -- , los conjuntos _N_, _Σ_ y el símbolo inicial _S_.  (0.5 pts.)
    - $N=\{$ programa, declaraciones, declaracion, tipo, lista_var, sentencias, sentencia, expresion $\}$
    - $\Sigma = \{$**int**, **float**, **identificador**, **;**, **if**, **else**, **(**, **)**, **while**, **=**, **,**, **numero** $\}$
    - $S = \{$ programa $\}$

2. Mostrar en el archivo el proceso de eliminación de ambigüedad o justificar, en caso de no ser necesario. (1 pts.). \

    Existe ambiguedad en la regla de expresion en la grámatica, esto debido a que se puede derivar, por ejemplo, la cadena $\text{numero} + \text{numero} * \text{numero}$ de diferentes formas:
    - expresion $\to$ expresion $\textbf{+}$ expresion $\to$ expresion $\textbf{+}$ expresion $\textbf{*}$ expresion
    - expresion $\to$ expresion $\textbf{*}$ expresion $\to$ expresion $\textbf{+}$ expresion $\textbf{*}$ expresion

    Y despues derivando número en cada una de las expresiones anteriores.
    Eliminaremos esto introduciendo diferentes niveles para operaciones, dependiendo de su orden de precedencia, la grámatica queda de la siguiente manera:
    - programa $\to$ declaraciones sentencias
    - declaraciones $\to$ declaraciones declaracion | declaracion
    - declaracion $\to$ tipo lista_var **;**
    - tipo $\to$ **int** | **float**
    - lista_var $\to$ lista_var **, identificador** $\mid$ **identificador**
    - sentencias $\to$ sentencias sentencia $\mid$ sentencia
    - sentencia $\to$ **identificador =** expresionS **;** $\mid$ **if (** expresionS **)** sentencias **else** sentencias $\mid$ **while (** expresionS **)** sentencias
    - expresionS $\to$  expresionS **+** expresionA $\mid$ expresionA
    - expresionA $\to$  expresionA **-** expresionB $\mid$ expresionB
    - expresionB $\to$  expresionB __*__ expresionC $\mid$ expresionC
    - expresionC $\to$  expresionC **/** expresionD $\mid$ expresionD
    - expresionD $\to$ **(** expresionS **)** $\mid$ **identificador** $\mid$ **numero**

3. Mostrar en el archivo el proceso de eliminación de la recursividad izquierda o justificar, en caso de no ser necesario. (1 pts.)

    Basándonos en la grámatica que dí en el inciso anterior las reglas que requieren eliminación de la recursividad izquierda son *declaraciones, lista_var, sentencias y todas las reglas de expresion, con excepción de expresionD*, al eliminarlas con el método visto nos queda de la siguiente forma:
    - programa $\to$ declaraciones sentencias
    - declaraciones $\to$ declaracion declaraciones'
    - declaraciones' $\to$ declaracion declaraciones' $\mid$ $\epsilon$
    - declaracion $\to$ tipo lista_var **;**
    - tipo $\to$ **int** | **float**
    - lista_var $\to$ **identificador** lista_var'
    - lista_var' $\to$ **, identificador** lista_var' $\mid$ $\epsilon$
    - sentencias $\to$ sentencia sentencias'
    - sentencias' $\to$ sentencia sentencias' $\mid$ $\epsilon$
    - sentencia $\to$ **identificador =** expresionS **;** $\mid$ **if (** expresionS **)** sentencias **else** sentencias $\mid$ **while (** expresionS **)** sentencias
    - expresionS $\to$  expresionA expresionS'
    - expresionS' $\to$  **+** expresionA expresionS' $\mid$ $\epsilon$
    - expresionA $\to$  expresionB expresionA'
    - expresionA' $\to$  **-** expresionB expresionA' $\mid$ $\epsilon$
    - expresionB $\to$  expresionC expresionB'
    - expresionB' $\to$  __*__ expresionC expresionB' $\mid$ $\epsilon$
    - expresionC $\to$  expresionD expresionC'
    - expresionC' $\to$  **/** expresionD expresionC' $\mid$ $\epsilon$
    - expresionD $\to$ **(** expresionS **)** $\mid$ **identificador** $\mid$ **numero**

4. Mostrar en el archivo el proceso de factorización izquierda o justificar, en caso de no ser necesario. (1 pts.)  

    La grámatica no requiere de factorización izquierda, las reglas que contienen "$\mid$" no son de la forma necesaria $\alpha \beta_1 \mid \dots \mid \alpha \beta_n $
5. Mostrar en el archivo los nuevos conjuntos _N_ y _P_. (0.5 pts.)

    - $N = \{$ programa, declaraciones, declaraciones', declaracion, tipo, lista_var, lista_var', sentencias, sentencias', sentencia, expresionS, expresionS', expresionA, expresionA', expresionB, expresionB', expresionC, expresionC', expresionD $\}$
    - $P = \{$
        - programa $\to$ declaraciones sentencias
        - declaraciones $\to$ declaracion declaraciones'
        - declaraciones' $\to$ declaracion declaraciones' $\mid$ $\epsilon$
        - declaracion $\to$ tipo lista_var **;**
        - tipo $\to$ **int** | **float**
        - lista_var $\to$ **identificador** lista_var'
        - lista_var' $\to$ **, identificador** lista_var' $\mid$ $\epsilon$
        - sentencias $\to$ sentencia sentencias'
        - sentencias' $\to$ sentencia sentencias' $\mid$ $\epsilon$
        - sentencia $\to$ **identificador =** expresionS **;** $\mid$ **if (** expresionS **)** sentencias **else** sentencias $\mid$ **while (** expresionS **)** sentencias
        - expresionS $\to$  expresionA expresionS'
        - expresionS' $\to$  **+** expresionA expresionS' $\mid$ $\epsilon$
        - expresionA $\to$  expresionB expresionA'
        - expresionA' $\to$  **-** expresionB expresionA' $\mid$ $\epsilon$
        - expresionB $\to$  expresionC expresionB'
        - expresionB' $\to$  __*__ expresionC expresionB' $\mid$ $\epsilon$
        - expresionC $\to$  expresionD expresionC'
        - expresionC' $\to$  **/** expresionD expresionC' $\mid$ $\epsilon$
        - expresionD $\to$ **(** expresionS **)** $\mid$ **identificador** $\mid$ **numero**

        $\}$

6. Definir el Analizador Léxico (lexer.ll) con las acciones léxicas correspondientes. (2 pts.)

7. Implementar el Analizador Sintáctico (Parser.cpp) de descenso recursivo, documentando las funciones de cada No-Terminal, de forma que el programa descrito en el archivo prueba sea reconocido y aceptado por el analizador resultante. (4 pts.)

---
#### Extras

8. Documentar el código. (0.25pts)
Se comentó el código.
9. Proponer 4 archivos de prueba nuevos, 2 válidos y 2 inválidos. (0.25pts)
10. Modificar el Makefile para poder simplificar el proceso de compilación de la práctica. (1pt)
Se implementó el makefile en el archivo dado, para compilar se puede hacer `make analyzer` y se ejecuta `.\analyzer prueba`
