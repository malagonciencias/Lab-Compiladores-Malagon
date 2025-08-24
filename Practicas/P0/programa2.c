#include <stdio.h>
#include <stdlib.h>

// Definimos pi, pero no muy bien
#define PI 3
// Si esta mal definido mejor lo indefinimos
#if PI == 3
#undef PI
// Redefinimos PI
#define PI (22/7)
#elif PI == 6
#error "Pi no vale 6!"
#else 
#define PI (22/7)
#endif

/*
Directivas nuevas:
#error
#if
#elif
#undef
*/

#define circ(r) (2 * PI * r)

int main(void) {
    printf("Hola mundo! \n");
    // Comentario de una línea!!!
    float circum = circ(9);
    printf("Resultado: %f\n", circum);
    return 0;
}