#include "./Headers/Celda.h"

Celda::Celda() {
    this->tipo = CAPA_AIRE;
    this->estado = true;
    this->ficha = Ficha();
    this->mina = Mina();
}

bool Celda::getEstado() {
    return this->estado;
}

void Celda::setEstado(bool estado) {
    this->estado = estado;
}

Capa Celda::getTipo() {
    return this->tipo;
}

void Celda::setTipo(Capa tipo) {
    this->tipo = tipo;
}

Ficha* Celda::getFicha() {
    return &this->ficha;
}
Ficha Celda::getCopiaFicha() {
    return this->ficha;
}

Mina* Celda::getMina() {
    return &this->mina;
}
Mina Celda::getCopiaMina() {
    return this->mina;
}

void Celda::setTurnosInactiva(int turnosInactiva){
    this->turnosInactiva = turnosInactiva;
}

int Celda::getTurnosInactiva(){
    return this->turnosInactiva;
}