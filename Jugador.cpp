#include "iostream"
#include <string>

#include "./Headers/Jugador.h"
#include "./Headers/Carta.h"
#include "./Headers/Enums.h"

using namespace std;

Jugador::Jugador() {
    this->nombre = "";
    this->soldados = 0;
    this->armamentos = 0;
    this->escudoActivo = false;
    this->cartas = new Cartas();
}

Jugador:: ~Jugador(){
    this->cartas->resetIter();
    for(int i = 0; i < this->cartas->getSize(); i++){
        delete this->cartas->getLData(i);
    }
    delete this->cartas;
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

void Jugador::agregarCarta(Carta* carta){
    this->cartas->add(carta);
}

void Jugador::imprimirCartas(){
    for(int i = 0; i < this->cartas->getSize(); i++){
        cout<< i+1 <<" Tipo De Carta: " <<this->cartas->getLData(i)->getStringTipoCarta()<<endl;
    }
}

Carta* Jugador::seleccionarCarta(int indiceCarta){
    return this->cartas->getLData(indiceCarta);
}

void Jugador::removerCarta(int indiceCarta){
    delete this->cartas->getLData(indiceCarta);
}

int Jugador::getCantidadDeCartas(){
    int cantidadDeCartas= 0;
    for(int i = 0; i < this->cartas->getSize(); i++){
        cantidadDeCartas++;
    }
    return cantidadDeCartas;
}
