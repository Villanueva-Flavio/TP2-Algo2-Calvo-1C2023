#include <iostream>
#include "celda.h"
#include "tablero.h"

void cargarSuelo(Tablero<Celda*>* suelo){
    for (int x = 0; x < suelo->getTamanioX(); x++) {
        for (int y = 0; y < suelo->getTamanioY(); y++){
           suelo->getTData(x,y,0)->setTipo(TIERRA);
        }
    }
};

void crearFicha(Tablero<Celda*>* suelo){
    suelo->getTData(9,9,0)->getFicha().setTipo(SOLDADO);
}

void moverFicha();

void mostrarEventos();

int main() {
    bool cortar = false;
    Tablero<Celda*>* juego = new Tablero<Celda*>(20, 20, 20);
    cargarSuelo(juego);
    crearFicha(juego);
    while (!cortar) {        
        moverFicha();
        mostrarEventos();
    }    
    delete juego;
    return 0;
}