#include <string>
#include "tablero.h"

#ifndef __CARTA_H__
#define __CARTA_H__

enum TipoCarta {AVION, BARCO, ATAQUE_QUIMICO, BOMBARDEO, OMITIR_TURNO, ESCUDO};

class Carta{
    private:

        TipoCarta carta;
        bool activa;
        int radioAccion;
        int cantidadBombas;

    public:

        //Constructor
        Carta(TipoCarta carta);

        //Permite al jugador acceder a la accion de la carta dependiendo de su tipo
        void usarCarta(bool &atributoJugador);

        //Permite al jugador acceder a la accion de la carta dependiendo de su tipo
        void usarCarta(Tablero tablero, int x, int y, int z);

        //Permite saber cual es el tipo de carta
        TipoCarta obteneterTipoCarta();

        //Permite saber si la carta esta activa
        bool cartaActiva();

    private:

        //Se inactivan las celdas del perimetro marcado por el radio
        void inactivarCeldas(Tablero tablero, int x, int y, int z);

        //Inactiva la cantidad de casillas indicadas en cantidad bombas de forma aleatoria dentro del rango
        void bombardearCeldas(Tablero tablero, int x, int y, int z);

        //Devuelve un reporte que indica si se alcanzo a un objetivo contrario y donde
        void obtenerReporte(Tablero tablero,int x, int y, int z);

        //Inactiva la casilla impactada
        void lanzarMisil(Tablero tablero, int x, int y, int z);

        //Devuelve las coordenadas dentro del radio definido
        std::string obtenerCoordenadas(int x, int y, int z);

        //Devuelve el contenido de la casilla
        std::string obtenerContenidoCasilla(int x, int y, int z);

        //Omite el turno del jugador continuo
        void activarAtributosJugador(bool &atributoJugador);

};

#endif