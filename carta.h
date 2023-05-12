#ifndef __CARTA_H__
#define __CARTA_H__
#include "Carta.h"
#include "tablero.h"
#include "celda.h"
enum TipoCarta {carta1, carta2, carta3, carta4, carta5, carta6};

class Carta{
    private:
        TipoCarta carta;
        bool activa;
        int turnosRestantes;
    public:

        Carta();

        TipoCarta getCarta();

        bool getActiva();

        int getTurnosRestantes();

        void setCarta(TipoCarta carta);

        void setActiva(bool activa);

        void setTurnosRestantes(int turnosRestantes);
};

Carta::Carta() {
    this->carta = carta1;
    this->activa = false;
    this->turnosRestantes = 0;
}

TipoCarta Carta::getCarta() {
    return this->carta;
}

bool Carta::getActiva() {
    return this->activa;
}

int Carta::getTurnosRestantes() {
    return this->turnosRestantes;
}

void Carta::setCarta(TipoCarta carta) {
    this->activa = false;
    switch(carta){
        case carta1:
            this->carta = carta1;
            this->turnosRestantes = 5;
            break;
        case carta2:
            this->carta = carta2;
            this->turnosRestantes = 5;
            break;
        case carta3:
            this->carta = carta3;
            this->turnosRestantes = 5;
            break;
        case carta4:
            this->carta = carta4;
            this->turnosRestantes = 5;
            break;
        case carta5:
            this->carta = carta5;
            this->turnosRestantes = 5;
            break;
        case carta6:
            this->carta = carta6;
            this->turnosRestantes = 5;
            break;
    }
}

void Carta::setActiva(bool activa) {
    this->activa = activa;
}

void Carta::setTurnosRestantes(int turnosRestantes) {
    this->turnosRestantes = turnosRestantes;
}
#include "./tpps/Carta.tpp"
#endif