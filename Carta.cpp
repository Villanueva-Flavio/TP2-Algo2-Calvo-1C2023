#include "Carta.h"

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

void Carta::usarCarta(){
    
    this->activa = false;

    switch(this->carta){
        case OMITIR_TURNO:
            omitirTurno();
            break;
        case ESCUDO:
            protegerFichas();
            break;
    }
}

void Carta::usarCarta(int x, int y, int z){

    this->activa = false;

    switch(this->carta){
        case AVION:
            this->radioAccion = 8;
            obtenerReporte(int x, int y, int z);
            break;
        case ATAQUE_QUIMICO:
            this->radioAccion = 5;
            inactivarCasillas(int x, int y, int z);
            break;
        case BOMBARDEO:
            this->radioAccion = 5;
            this->cantidadBombas = 4;
            bombardearZona(int x, int y, int z);
            break;
        case BARCO:
            lanzarMisil(int x, int y, int z);
            break;
    }
}

TipoCarta Carta::getCarta() {
    return this->carta;
}

bool Carta::getActiva() {
    return this->activa;
}
