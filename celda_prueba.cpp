#include <iostream>
#include "celda.h"

int main() {
    Celda celdita(TIERRA);
    std::cout << "El enumerado está en la posición: " << celdita.getTipo() << std::endl;
    if (celdita.getTipo() == TIERRA){
        std::cout << "Hello wordl!\n";
    }
    return 0;
}