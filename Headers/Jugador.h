#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <string>
#include "../EasyBMP/EasyBMP_DataStructures.h"

class Jugador{
    private:
        std::string nombre;
        int soldados;
        int minas;
        int armamentos;
        bool escudoActivo; //yenny nuevo
        bool omitirTurno;//yenny nuevo
        RGBApixel color;
        //Carta *cartas;
    public:
            
            Jugador();
    
            std::string getNombre();
    
            int getSoldados();
    
            int getMinas();
    
            int getArmamentos();
    
            //Carta* getCartas();
    
            void setNombre(std::string nombre);
    
            void setSoldados(int soldados);
    
            void setMinas(int minas);
    
            void setArmamentos(int armamentos);

            // void setCartas(Carta* cartas);

            //Memueve el escudo activado por una carta
            void desactivarEscudo();//yenny nuevo

            //Habilita al jugador a participar en las rondas
            void reactivarJugador();//yenny nuevo

            void setColor(RGBApixel color);

            RGBApixel getColor();

};

// #include "../TPPs/Carta.tpp"
#endif