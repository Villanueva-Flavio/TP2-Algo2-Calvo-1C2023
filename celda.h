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

        Celda(TipoCelda tipoCelda, TipoContenido contenido);

        TipoCelda getTipo();

        void setTipo(TipoCelda tipo);

        void setEstado(bool estado);

        bool getEstado();
};

Celda::Celda(TipoCelda tipoCelda, TipoContenido contenido) {
    this->tipo = tipoCelda;
    this->ficha.setTipo(contenido);
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