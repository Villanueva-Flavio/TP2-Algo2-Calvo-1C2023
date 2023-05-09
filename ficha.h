#include <string>

enum TipoContenido {SOLDADO, ARMAMENTO, MINA, CARTA, VACIO};
enum TipoFicha {SOLDADO, TANQUE, SUBMARINO, AVION};

class Ficha{
    private:
        int jugadorOwner;
        TipoFicha tipo; 
    public:
        Ficha(TipoContenido contenido, TipoFicha ficha);
        void setTipo(TipoFicha tipo);
        TipoFicha Ficha::getTipo();
        int getJugadorOwner();
        void setJugadorOwner(int jugadorOwner);
};

// Constructor
Ficha::Ficha(TipoContenido contenido, TipoFicha ficha) {
    this->tipo = ficha;
    this->jugadorOwner = 0;
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
void Ficha::setTipo(TipoFicha tipo) {
    this->tipo = tipo;
}

// Devuelve el tipo enum de la ficha
TipoFicha Ficha::getTipo() {
    return this->tipo;
}