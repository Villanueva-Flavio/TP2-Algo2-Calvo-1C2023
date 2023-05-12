#ifndef __FICHA_H__
#define __FICHA_H__

enum TipoContenido {SOLDADO, TANQUE, SUBMARINO, AVION, MINA, CARTA, VACIO};

class Ficha{
    private:
        int jugadorOwner;
        TipoContenido tipo; 
    public:
        Ficha();
        void setTipo(TipoContenido tipo);
        TipoContenido getTipo();
        int getJugadorOwner();
        void setJugadorOwner(int jugadorOwner);
};
#include "./tpps/ficha.tpp"
#endif