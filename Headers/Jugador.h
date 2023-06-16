#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <string>
#include "carta.h"
#include "../EasyBMP/EasyBMP_DataStructures.h"

typedef Lista<Carta*> Cartas;

class Jugador{
    private:
        std::string nombre;
        int soldados;
        int minas;
        int armamentos;
        bool escudoActivo; 
        RGBApixel color;
        Cartas* cartas;
    public:
            
        Jugador();

        std::string getNombre();

        int getSoldados();

        int getMinas();

        int getArmamentos();

        void setNombre(std::string nombre);

        void setSoldados(int soldados);

        void setMinas(int minas);

        void setArmamentos(int armamentos);

        //Activa el escudo del jugador
        void activarEscudo();

        //Remueve el escudo del jugador
        void desactivarEscudo();

        void setColor(RGBApixel color);

        RGBApixel getColor();

        //Pre:debe recibir un punto a una carta
        //Post: debe agregar la carta recibida como parametro a la lista de cartas
        void agregarCarta(Carta* carta);

        //Pre:El jugador debe tener cartas
        //Post:Devuelve por consola la lista de cartas que posee el jugador
        void imprimirCartas();

        //Pre:se tiene que recibir un indice valido
        //Post: devuelve un puntero a la carta correspondiente al indice ingresado
        Carta* seleccionarCarta(int carta);

        //Pre:no tiene
        //Post: devuelve la cantidad de cartas que tiene el jugador
        int getCantidadDeCartas();

};

#endif