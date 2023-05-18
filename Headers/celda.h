#include "ficha.h"
#ifndef __CELDA_H__
#define __CELDA_H__

enum TipoCelda {CELDA_TIERRA, CELDA_AGUA, CELDA_AIRE};

class Celda {
    private:
        TipoCelda tipo;
        bool activa;
        Ficha ficha;
        //Revisar en reunion
        int totalTurnosInactiva;
        int contadorTurnosInactiva;

    public:

        Celda();

        TipoCelda getTipo();

        void setTipo(TipoCelda tipo);

        void setEstado(bool estado);

        bool getEstado();

        Ficha getFicha();

        void setTurnosInactiva(int turnosInactiva);

        int getTurnosInactiva();

        void reactivarCeldaInactiva();
};
#endif