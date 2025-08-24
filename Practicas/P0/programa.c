#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926535897

#ifdef PI
#define area(r) (PI * r * r)
#else
#define area(r) (3.1416 * r * r)
#endif

int main(void) {
    printf("Hola mundo! \n");
    // Comentario de una línea!!!
    float mi_area = area(3);
    printf("Resultado: %f\n", mi_area);
    return 0;
}