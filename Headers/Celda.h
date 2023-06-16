#include "Ficha.h"
#ifndef __CELDA_H__
#define __CELDA_H__

class Celda {
    private:
        Capa tipo;
        bool estado;
        Ficha ficha;
        int turnosInactiva;

    public:
        Celda();

        Capa getTipo();

        void setTipo(Capa tipo);

        void setEstado(bool estado);

        bool getEstado();

        Ficha* getFicha();

        Ficha getCopiaFicha();

        void setTurnosInactiva(int turnosInactiva);

        int getTurnosInactiva();
};
#endif