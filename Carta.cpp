#include "Carta.h"
#include "tablero.h"
#include "celda.h"
#include <string>
using namespace std;

Carta::Carta(TipoCarta carta) {
    
    this->activa = true;
    this->radioAccion = NULL;
    this->cantidadBombas = NULL;

    switch(carta){
        case AVION:
            this->carta = AVION;
            break;
        case ATAQUE_QUIMICO:
            this->carta = ATAQUE_QUIMICO;
            break;
        case BOMBARDEO:
            this->carta = BOMBARDEO;
            break;
        case BARCO:
            this->carta = BARCO;
            break;
        case OMITIR_TURNO:
            this->carta = OMITIR_TURNO;
            break;
        case ESCUDO:
            this->carta = ESCUDO;
            break;
    }
}

 void Carta::usarCarta(bool &atributoJugador){
    
    this->activa = false;

    switch(this->carta){
        case OMITIR_TURNO:
            //se pasa por parametros jugador continuo
            activarAtributosJugador(atributoJugador);
            break;
        case ESCUDO:
            activarAtributosJugador(atributoJugador);
            break;
    }
} 

 void Carta::usarCarta(Tablero tablero, int x, int y, int z){

    this->activa = false;

    switch(this->carta){
        case AVION:
            this->radioAccion = 8;
            obtenerReporte(tablero,x, y, z);
            break;
        case ATAQUE_QUIMICO:
            this->radioAccion = 5;
            inactivarCeldas(tablero,x, y, z);
            break;
        case BOMBARDEO:
            this->radioAccion = 5;
            this->cantidadBombas = 4;
            bombardearZona(tablero,x, y, z);
            break;
        case BARCO:
            lanzarMisil(tablero,x, y, z);
            break;
    }
}

TipoCarta Carta::obteneterTipoCarta() {
    return this->carta;
}

bool Carta::cartaActiva() {
    return this->activa;
}

void Carta::inactivarCeldas(Tablero tablero, int x, int y, int z){
    
    int radio= this->radioAccion;
    Celda copiaCelda = new Celda() ;
}

void Carta::bombardearCeldas(Tablero tablero, int x, int y, int z){

}

void Carta::obtenerReporte(Tablero tablero, int x, int y, int z){

}

void Carta::lanzarMisil(Tablero tablero, int x, int y, int z){

}

string Carta::obtenerCoordenadas(int x, int y, int z){

}

string Carta::obtenerContenidoCasilla(int x, int y, int z){

}

void Carta::activarAtributosJugador(bool &atributoJugador){
    if(!atributoJugador){
        atributoJugador = true;
    }
} 