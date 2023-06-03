#include <string>
#include "Tablero.h"
#include "Celda.h"

#ifndef __CARTA_H__
#define __CARTA_H__

enum TipoCarta {AVION_RADAR,BARCO_MISIL, ATAQUE_QUIMICO, BOMBARDEO, OMITIR_TURNO, ESCUDO};

class Carta{
    private:

        TipoCarta carta;
        bool cartaActiva;
        int radioAccion;
        int cantidadBombas;
        int cantidadRondas;

    public:

        //Constructor
        Carta(TipoCarta carta);

        //Permite al jugador acceder a la accion de la carta dependiendo de su tipo
        void usarCarta(bool &atributoJugador);

        //Permite al jugador acceder a la accion de la carta dependiendo de su tipo
        void usarCarta(Tablero<Celda*>* tablero, int x, int y, int z);

        //Permite saber cual es el tipo de carta
        TipoCarta getTipoCarta();

        //Permite saber si la carta esta activa
        bool getCartaActiva();

    private:

        //Se inactivan las celdas del perimetro marcado por el radio
        void inactivarCeldas(Tablero<Celda*>* tablero,int x, int y, int z);

        //Inactiva la cantidad de casillas indicadas en cantidad bombas de forma aleatoria dentro del rango
        void bombardearCeldas(Tablero<Celda*>* tablero,int x, int y, int z);

        //Devuelve un reporte que indica si se alcanzo a un objetivo contrario y donde 
        void obtenerReporte(Tablero<Celda*>* tablero, int x, int y, int z);

        //Inactiva la casilla impactada
        void lanzarMisil(Tablero<Celda*>* tablero, int x, int y, int z);

        //Omite el turno del jugador continuo
        void activarAtributosJugador(bool &atributoJugador);

        //Imprime el reporte de los efectos de las
        void imprimirReporte(std::string reporte);

        std::string getStringTipoFicha(TipoContenido);

        //Devuelve la cantidad de turnos que va a permanecer la casilla dependiendo de la distancia a la que se encuentre del centrio de la explosion
        int getTurnosInactiva(int puntoX, int puntoY, int puntoZ, int centroX, int centroY, int centroZ);
};

#endif