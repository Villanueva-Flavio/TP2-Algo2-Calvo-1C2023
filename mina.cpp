#include "mina.h"


Mina::Mina(){

    estado = COLOCADA;
}


char Mina::getEstado() const {

    return estado;
}

void Mina::setEstado(EstadoMina  nuevoEstado){

    estado = nuevoEstado;
}

void Mina::colocar() {

    estado = COLOCADA;
}

void Mina::explotar() {

    estado = CASILLA_INACTIVA;
}

void Mina::eliminar() {

    estado = ELIMINADA;
}