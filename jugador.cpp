#include "jugador.h"
#include "Carta.h"

Jugador::Jugador() {
    this->nombre = "";
    this->soldados = 0;
    this->minas = 0;
    this->armamentos = 0;
    this->escudoActivo = false;
    this->omitirTurno = false;
   // this->cartas = new Carta;
}

std::string Jugador::getNombre() {
    return this->nombre;
}

int Jugador::getSoldados() {
    return this->soldados;
}

int Jugador::getMinas() {
    return this->minas;
}

int Jugador::getArmamentos() {
    return this->armamentos;
}

/* Carta* Jugador::getCartas() {
    return this->cartas;
} */

void Jugador::setNombre(std::string nombre) {
    this->nombre = nombre;
}

void Jugador::setSoldados(int soldados) {
    this->soldados = soldados;
}

void Jugador::setMinas(int minas) {
    this->minas = minas;
}

void Jugador::setArmamentos(int armamentos) {
    this->armamentos = armamentos;
}

/* void Jugador::setCartas(Carta* cartas) {
    this->cartas = cartas;
} */

void Jugador::desactivarEscudo(){
    if(this->escudoActivo){
        this->escudoActivo = false;
    }
}

void Jugador::reactivarJugador(){
    if(this->omitirTurno){
        this->omitirTurno = false;
    }
}