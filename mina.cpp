#include "mina.h"


Mina::Mina(){

    this->estado = COLOCADA;
}


EstadoMina Mina::getEstado() const {

    return this->estado;
}

void Mina::setEstado(EstadoMina  nuevoEstado){

    this->estado = nuevoEstado;
}

void Mina::colocar() {

    this->estado = COLOCADA;
}

void Mina::explotar() {

    this->estado = CASILLA_INACTIVA;
}

void Mina::eliminar() {

    this->estado = ELIMINADA;
}