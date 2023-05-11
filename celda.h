#include "ficha.h"
#ifndef __CELDA_H__
#define __CELDA_H__

enum TipoCelda {TIERRA, AGUA, AIRE};

class Celda {
    private:
        TipoCelda tipo;
        bool estado;
        Ficha ficha;

    public:

        Celda();

        TipoCelda getTipo();

        void setTipo(TipoCelda tipo);

        void setEstado(bool estado);

        bool getEstado();
};

Celda::Celda() {
    this->tipo = AIRE;
    this->ficha->setTipo(VACIO);
}

bool Celda::getEstado() {
    return this->estado;
}

void Celda::setEstado(bool estado) {
    this->estado = estado;
}

TipoCelda Celda::getTipo() {
    return this->tipo;
}

void Celda::setTipo(TipoCelda tipo) {
    this->tipo = tipo;
}

#endif