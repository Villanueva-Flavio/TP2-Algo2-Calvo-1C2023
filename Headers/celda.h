#include "ficha.h"
#ifndef __CELDA_H__
#define __CELDA_H__

enum Capa {CAPA_ARENA, CAPA_AGUA, CAPA_TIERRA, CAPA_PASTO, CAPA_BORDE, CAPA_MINA, CAPA_FUEGO, CAPA_AIRE};

class Celda {
    private:
        Capa tipo;
        bool estado;
        Ficha ficha;
        //Revisar en reunion
        int totalTurnosInactiva;
        int contadorTurnosInactiva;

    public:

        Celda();

        Capa getTipo();

        void setTipo(Capa tipo);

        void setEstado(bool estado);

        bool getEstado();

        Ficha getFicha();

        void setTurnosInactiva(int turnosInactiva);

        int getTurnosInactiva();

        void reactivarCeldaInactiva();
};
#endif