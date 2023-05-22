#include "./Headers/celda.h"

Celda::Celda() {
    this->tipo = CAPA_AIRE;
    this->estado = true;
    this->ficha = Ficha();
    this->contadorTurnosInactiva = 0;
    this->totalTurnosInactiva = 0;
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

Ficha Celda::getFicha() {
    return this->ficha;
}

void Celda::setTurnosInactiva(int turnosInactiva){
    this->totalTurnosInactiva = turnosInactiva;
}

int Celda::getTurnosInactiva(){
    return this->totalTurnosInactiva;
}

void Celda::reactivarCeldaInactiva(){

    if(this->estado){

        if(this->totalTurnosInactiva != this->contadorTurnosInactiva ){
            this->contadorTurnosInactiva ++;
        }else{
            this->contadorTurnosInactiva = 0;
            this->totalTurnosInactiva = 0;
            this->estado = true;
        }
    }
    
}