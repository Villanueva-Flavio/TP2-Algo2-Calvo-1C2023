#include "./Headers/Celda.h"

Celda::Celda() {
    this->tipo = CAPA_AIRE;
    this->estado = true;
    this->ficha = Ficha();
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