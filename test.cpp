#include <iostream>
#include "celda.h"
#include "tablero.h"

using namespace std;

int main() {
    Tablero<Celda*>* juego = new Tablero<Celda*>(20, 20, 20);
    delete juego;
    return 0;
}