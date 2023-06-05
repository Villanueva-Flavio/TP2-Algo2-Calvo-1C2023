#include "Enums.h"
#ifndef __FICHA_H__
#define __FICHA_H__

class Ficha{
    private:
        int jugadorOwner;
        int enumerador;
        TipoContenido tipo; 
    public:
        Ficha();
        void setTipo(TipoContenido tipo);
        TipoContenido getTipo();
        int getJugadorOwner();
        void setJugadorOwner(int jugadorOwner);
        int getNumFicha();
        void setNumFicha(int numero);
};
#endif