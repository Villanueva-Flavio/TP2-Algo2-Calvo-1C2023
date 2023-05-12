#include "ficha.h"
#ifndef __CELDA_H__
#define __CELDA_H__

enum TipoCelda {TIERRA, AGUA, AIRE};

class Celda {
    private:
        TipoCelda tipo;
        bool estado;
        Ficha ficha;
        
    public:
        Celda();
        TipoCelda getTipo();
        void setTipo(TipoCelda tipo);
        void setEstado(bool estado);
        bool getEstado();
        Ficha getFicha();

};
#include "tpps/celda.tpp"
#endif