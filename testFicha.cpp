#include "celda.h"
#include <iostream>

int main() {
    Celda* celda = new Celda(TIERRA, VACIO); // Creo la Celda
    celda->makeFicha(SOLDADO); // Creo la ficha
    std::cout << "La ficha tiene asigado un enum el cual se encuentra en la posicición: " << (celda->getFicha() != nullptr) ? celda->getFicha()->getTipo() : VACIO << '\n';
    celda->delFicha(); // Borro la ficha
    std::cout << '\n';
    if (celda->getFicha() == nullptr) std::cout << "Se eliminó la ficha" << '\n';
    else std::cout << "No se ha eliminado la ficha" << '\n';
    delete celda; // Borro la celda
    return 0;
}   

// [OUTPUT ESPERADO]
// La ficha tiene asigado un enum el cual se encuentra en la posicición: 1
// Se eliminó la ficha
// ==58156== 
// ==58156== HEAP SUMMARY:
// ==58156==     in use at exit: 0 bytes in 0 blocks
// ==58156==   total heap usage: 4 allocs, 4 frees, 73,752 bytes allocated
// ==58156== 
// ==58156== All heap blocks were freed -- no leaks are possible
// ==58156== 
// ==58156== For lists of detected and suppressed errors, rerun with: -s
// ==58156== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)