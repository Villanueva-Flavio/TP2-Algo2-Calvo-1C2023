#include "tablero.h"
#include "celda.h"
#include <typeinfo>
#include <iostream>

typedef Tablero<Celda*> Juego;

void cargarTablero(Juego& batallaDigital){
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            batallaDigital.getTData(i,j,0)->setTipo(TIERRA);
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << batallaDigital.getTData(i,j,0)->getTipo();
        }
        std::cout << std::endl;
    }
}

int main() {
    Juego* batallaDigital = new Juego(5, 5, 5);
    cargarTablero(*batallaDigital);
    delete batallaDigital;
    return 0;
}