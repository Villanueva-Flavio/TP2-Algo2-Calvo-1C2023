#include "./Headers/Mina.h"

Mina::Mina(){
    this->activa = false;
    this->tipo = INEXISTENTE;
}

bool Mina::getMinaActiva() {
    return this->activa;
}

tipoMina Mina::getTipoMina() {
    return this->tipo;
}

void Mina::setMinaActiva(bool estado) {
    this->activa = estado;
}

void Mina::setTipoMina(tipoMina tipo) {
    this->tipo = tipo;
}