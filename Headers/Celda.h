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
        //Pre: no tiene
        //Post: crea una instancia de celda
        Celda();

        //Pre:no tiene
        //Post:devuelve el tipo de capa del que pertenece la celda
        Capa getTipo();

        //Pre: debe recibir un enum tipoCarta
        //Post: asigna el tipo de carta especificada por argumento
        void setTipo(Capa tipo);

        //Pre: recibe el estado que se le quiere asignar a la ficha 
        //Post: asigna el estado pasado por parametro
        void setEstado(bool estado);
        
        //Pre: no tiene
        //Post: devuelve true si la celda esta activa y false si esta inactiva
        bool getEstado();
        
        //Pre:no tiene
        //Post:devuelve un puntero a la ficha que se encuentra dentro de la celda
        Ficha* getFicha();

        //Pre: no tiene
        //Post: devuelve una copia de la ficha que se encuentra dentro de la celda
        Ficha getCopiaFicha();

        //Pre:recibe un numero con la cantidad de rondas que hay que dejar a la celda inactiva
        //Post: asigna la cantidad de rondas que la celda tiene que permancer inactiva
        void setTurnosInactiva(int turnosInactiva);

        //Pre: no tiene
        //Post: devuelve la cantidad de turnos que la celda debe permanecer inactiva
        int getTurnosInactiva();
};
#endif