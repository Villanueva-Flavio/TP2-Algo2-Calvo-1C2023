#ifndef __FICHA_H__
#define __FICHA_H__

#include <string>

enum TipoContenido {SOLDADO, TANQUE, BARCO, SUBMARINO, AVION, MINA, CARTA, VACIO};

class Ficha{
    private:
        int jugadorOwner;
        int fichaNumero;
        TipoContenido tipo;

    public:
        Ficha();
        void setTipo(TipoContenido tipo);
        TipoContenido getTipo();
        int getJugadorOwner();
        void setJugadorOwner(int jugadorOwner);
};

#include "tpps/ficha.cpp"
#endif