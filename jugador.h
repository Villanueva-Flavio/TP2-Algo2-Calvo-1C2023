#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <string>
#include "carta.h"
#include "mina.h"

class Jugador{
    private:
        std::string nombre;
        int soldados;
        int numMinas;      //
        int armamentos;
        Carta *cartas; // ver esto
    public:
            
            Mina* minas;    // agregado
            
            Jugador();

            ~Jugador();    // agregado
    
            std::string getNombre();
    
            int getSoldados();
    
            int getNumMinas();  //
    
            int getArmamentos();
    
            Carta* getCartas();
    
            void setNombre(std::string nombre);
    
            void setSoldados(int soldados);
    
            void setNumMinas(int minas);    //
    
            void setArmamentos(int armamentos);
    
            void setCartas(Carta* cartas);

};

Jugador::Jugador() {
    this->nombre = "";
    this->soldados = 0;
    this->numMinas = 0;
    this->armamentos = 0;
    this->cartas = new Carta;
    this->minas = new Mina[numMinas];    //
}

Jugador::~Jugador() {
    delete[] this->minas;
}

std::string Jugador::getNombre() {
    return this->nombre;
}

int Jugador::getSoldados() {
    return this->soldados;
}

int Jugador::getNumMinas() {
    return this->numMinas;
}

int Jugador::getArmamentos() {
    return this->armamentos;
}

Carta* Jugador::getCartas() {
    return this->cartas;
}

void Jugador::setNombre(std::string nombre) {
    this->nombre = nombre;
}

void Jugador::setSoldados(int soldados) {
    this->soldados = soldados;
}

void Jugador::setNumMinas(int minas) {
    this->numMinas = numMinas;

}

void Jugador::setArmamentos(int armamentos) {
    this->armamentos = armamentos;
}

void Jugador::setCartas(Carta* cartas) {
    this->cartas = cartas;
}

#endif