#include "./Headers/celda.h"

Celda::Celda() {
    this->tipo = CELDA_AIRE;
    this->activa = true;
    this->ficha = Ficha();
    this->contadorTurnosInactiva = 0;
    this->totalTurnosInactiva = 0;
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

void Celda::setTurnosInactiva(int turnosInactiva){
    this->totalTurnosInactiva = turnosInactiva;
}

int Celda::getTurnosInactiva(){
    return this->totalTurnosInactiva;
}

void Celda::reactivarCeldaInactiva(){

    if(this->activa){

        if(this->totalTurnosInactiva != this->contadorTurnosInactiva ){
            this->contadorTurnosInactiva ++;
        }else{
            this->contadorTurnosInactiva = 0;
            this->totalTurnosInactiva = 0;
            this->activa = true;
        }
    }
    
}