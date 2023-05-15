#include "./Headers/celda.h"

Celda::Celda() {
    this->tipo = CELDA_AIRE;
    this->activa = true;
    this->ficha = Ficha();
}

bool Celda::getEstado() {
    return this->activa;
}

void Celda::setEstado(bool estado) {
    this->activa = estado;
}

TipoCelda Celda::getTipo() {
    return this->tipo;
}

void Celda::setTipo(TipoCelda tipo) {
    this->tipo = tipo;
}

Ficha Celda::getFicha() {
    return this->ficha;
}