#include "mina.h"


Mina::Mina() : estado('c') {}


char Mina::obtenerEstado() const {

    return estado;
}

void Mina::cambiarEstado(char nuevoEstado){

    estado = nuevoEstado;
};