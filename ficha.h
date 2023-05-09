#ifndef __FICHA_H__
#define __FICHA_H__

#include <string>

enum TipoContenido {SOLDADO, TANQUE, SUBMARINO, AVION, MINA, CARTA, VACIO};

class Ficha{
    private:
        int jugadorOwner;
        TipoContenido tipo; 
    public:
        Ficha(TipoContenido tipo);
        void setTipo(TipoContenido tipo);
        TipoContenido getTipo();
        int getJugadorOwner();
        void setJugadorOwner(int jugadorOwner);
};

// Constructor
Ficha::Ficha(TipoContenido tipo) {
    this->tipo = tipo;
    this->jugadorOwner = -1;
}

// Devuelve ID del jugador al que le pertenece la ficha
int Ficha::getJugadorOwner() {
    return this->jugadorOwner;
}

// Modifica el ID del jugador al que le pertenece la ficha
void Ficha::setJugadorOwner(int jugadorOwner) {
    this->jugadorOwner = jugadorOwner;
}

// Tipos que admite: SOLDADO, TANQUE, AVION y SUBMARINO.
// Modifica el tipo de fichea, se le debe pasar un enum { setTipo(TipoFicha) }
void Ficha::setTipo(TipoContenido tipo) {
    this->tipo = tipo;
}

// Devuelve el tipo enum de la ficha
TipoContenido Ficha::getTipo() {
    return this->tipo;
}

#endif