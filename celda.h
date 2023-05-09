#include "ficha.h"
#ifndef __CELDA_H__
#define __CELDA_H__

enum TipoCelda {TIERRA, AGUA, AIRE};

class Celda {
    private:
        TipoCelda tipo;
        bool estado;
        Ficha* ficha;

    public:

        Celda(TipoCelda tipoCelda, TipoContenido contenido);

        TipoCelda getTipo();

        void setTipo(TipoCelda tipo);

        void setEstado(bool estado);

        bool getEstado();

        void makeFicha(TipoContenido contenido);

        void delFicha();

        Ficha* getFicha();
};

// Este constructor recibe dos parámetros del tipo enum, (elemento, tipoFicha) elemento puede ser TIERRA, AGUA y AIRE. Para tipoFicha revisar enums de ficha.h
Celda::Celda(TipoCelda tipoCelda, TipoContenido contenido) {
    this->tipo = tipoCelda;
    this->ficha = (contenido != VACIO) ? new Ficha(contenido) : nullptr;
}

// Crea una ficha en el heap
void Celda::makeFicha(TipoContenido contenido){
    this->ficha = new Ficha(contenido);
}

// Borra la ficha del heap si es que el puntero a 'Ficha' no apunta al puntero nulo
void Celda::delFicha(){
    if (this->ficha != nullptr) {
        delete this->ficha;
        this->ficha = nullptr;
    }
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

// Devuelve el puntero a ficha
Ficha* Celda::getFicha() {
    return this->ficha;
}

// IMPORTANTE, ACORDARSE DE MATAR TODAS LAS FICHAS AL CERRAR EL JUEGO, NO SE PUEDE IMPLEMENTAR DESTRUCTOR

#endif