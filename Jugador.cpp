#include "iostream"
#include <string>

#include "./Headers/Jugador.h"
#include "./Headers/carta.h"
#include "./Headers/Enums.h"

using namespace std;

Jugador::Jugador() {
    this->nombre = "";
    this->soldados = 0;
    this->armamentos = 0;
    this->escudoActivo = false;
    this->color = {0,0,0,0};
    this->cartas = new Cartas();
}

string Jugador::getNombre() {
    return this->nombre;
}

int Jugador::getSoldados() {
    return this->soldados;
}

int Jugador::getMinas() {
    return this->minas;
}

int Jugador::getArmamentos() {
    return this->armamentos;
}

void Jugador::setNombre(string nombre) {
    this->nombre = nombre;
}

void Jugador::setSoldados(int soldados) {
    this->soldados = soldados;
}

void Jugador::setMinas(int minas) {
    this->minas = minas;
}

void Jugador::setArmamentos(int armamentos) {
    this->armamentos = armamentos;
}


void Jugador::desactivarEscudo(){
  this->escudoActivo = false;
}

void Jugador::activarEscudo(){
   this->escudoActivo = true;
}


void Jugador::setColor(RGBApixel rgb){
    this->color = rgb;
}

RGBApixel Jugador::getColor(){
    return this->color;
}

void Jugador::agregarCarta(Carta* carta){
    this->cartas->add(carta);
}

void Jugador::imprimirCartas(){
    for(int i = 0; i < this->cartas->getSize(); i++){
        cout<< i+1 <<" Tipo De Carta: " <<this->cartas->getLData(i)->getStringTipoCarta()<<endl;
    }
}

Carta* Jugador::seleccionarCarta(int indiceCarta){
    //Falta validacion
    return this->cartas->getLData(indiceCarta);
}

int Jugador::getCantidadDeCartas(){
    int cantidadDeCartas= 0;
    for(int i = 0; i < this->cartas->getSize(); i++){
        cantidadDeCartas++;
    }
    return cantidadDeCartas;
}