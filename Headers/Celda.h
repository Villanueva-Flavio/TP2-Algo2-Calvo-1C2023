#include "Ficha.h"
#include "Mina.h"
#ifndef __CELDA_H__
#define __CELDA_H__
enum Capa {CAPA_ARENA, CAPA_AGUA, CAPA_TIERRA, CAPA_PASTO, CAPA_BORDE, CAPA_MINA, CAPA_FUEGO, CAPA_AIRE};

class Celda {
    private:
        Capa tipo;
        bool estado;
        Ficha ficha;
        Mina  mina;
        int turnosInactiva;

    public:
        Celda();

        Capa getTipo();

        void setTipo(Capa tipo);

        void setEstado(bool estado);

        bool getEstado();

        Ficha* getFicha();

        Ficha getCopiaFicha();

        Mina* getMina();

        Mina getCopiaMina();

        //Post: asigna la cantidad de turnos inactiva que debe permanecer la celda
        void setTurnosInactiva(int turnosInactiva);

        //Post: obtiene la cantidad de turnos inactiva que debe permanecer la celda
        int getTurnosInactiva();
};
#endif