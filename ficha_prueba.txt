#include "ficha.h"
#include <iostream>

int main() {
    // Sets
    ficha soldado;
    soldado.setTipo("soldado");
    soldado.setActiva(true);
    soldado.setVida(-100);
    soldado.setCoords(2,1,5);
    // Gets
    std::cout << "El tipo de ficha es: '" << soldado.getTipo() << "'" << ".\n";
    std::cout << "Actualmente el " << soldado.getTipo() << " se encuentra en las coordenadas (" << soldado.getCoords('x') << ", " << soldado.getCoords('y') << ", " << soldado.getCoords('z') << ")" << " y su estado es " << soldado.getActiva() << ". (0 es false y 1 es true)\n";
    std::cout << soldado.getTipo() << " tiene " << soldado.getVida() << " de vida.\n"; 
    return 0;
}

/*
    ._______________________________________________.
   | OUTPUT DEL EJECUTABLE, COMPILADO CON VALGRIND: |

El tipo de ficha es: 'soldado'.
Actualmente el soldado se encuentra en las coordenadas (2, 1, 5) y su estado es 1. (0 es false y 1 es true)
soldado tiene 100 de vida.
==48807== 
==48807== HEAP SUMMARY:
==48807==     in use at exit: 0 bytes in 0 blocks
==48807==   total heap usage: 8 allocs, 8 frees, 73,777 bytes allocated
==48807== 
==48807== All heap blocks were freed -- no leaks are possible
==48807== 
==48807== For lists of detected and suppressed errors, rerun with: -s
==48807== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/