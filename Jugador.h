#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <string>
#include "Carta.h"
#include "EasyBMP/EasyBMP_DataStructures.h"

class Jugador{
    private:
        std::string nombre;
        int soldados;
        int minas;
        int armamentos;
        bool escudoActivo; 
        Lista<Carta*>* cartas;
    public:
        //PRE: no tiene
        //POST: crea una isntancia de jugador
        Jugador();

        //PRE: no tiene
        //POST: destruye la instancia jugador y libera la memoria dinamica usada
        ~Jugador();

        //POST: Devuelve el nombre del jugador
        std::string getNombre();

        //POST: Devuelve la cantidad de soldados del jugador
        int getSoldados();

        //POST: Devuelve la cantidad de minas del jugador
        int getMinas();

        //POST: Devuelve la cantidad de armamentos del jugador
        int getArmamentos();

        //PRE: Recibe el string de nombre del jugador
        //POST: Setea el nombre del jugador
        void setNombre(std::string nombre);

        //PRE: Recibe un int de la cantidad de soldados
        //POST: Setea la cantidad de soldados
        void setSoldados(int soldados);

        //PRE: Recibe un int de la cantidad de minas
        //POST: Setea la cantidad de minas
        void setMinas(int minas);

        //PRE: Recibe un int de la cantidad de armamentos
        //POST: Setea la cantidad de armamentos
        void setArmamentos(int armamentos);

        //Activa el escudo del jugador
        void activarEscudo();

        //Remueve el escudo del jugador
        void desactivarEscudo();

        //Pre:debe recibir un punto a una carta
        //Post: debe agregar la carta recibida como parametro a la lista de cartas
        void agregarCarta(Carta* carta);

        //Pre:El jugador debe tener cartas
        //Post:Devuelve por consola la lista de cartas que posee el jugador
        void imprimirCartas();

        //Pre:se tiene que recibir un indice valido
        //Post: devuelve un puntero a la carta correspondiente al indice ingresado
        Carta* seleccionarCarta(int indiceCarta);

        //Pre:se tiene que recibir el indice de la carta que se desea remover
        //Post: remueve la carta del mazo del indice indicado
        void removerCarta(int indiceCarta);

        //Post: devuelve la cantidad de cartas que tiene el jugador
        int getCantidadDeCartas();

};

#endif