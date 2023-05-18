#include <string>
#include "tablero.h"
#include "celda.h"

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
        template <class Celda> 
        void usarCarta(Tablero<Celda> &, int x, int y, int z);

        //Permite saber cual es el tipo de carta
        TipoCarta getTipoCarta();

        //Permite saber si la carta esta activa
        bool getCartaActiva();

    private:

        //Se inactivan las celdas del perimetro marcado por el radio
        template <class Celda> 
        void inactivarCeldas(Tablero<Celda> &,int x, int y, int z);

        //Inactiva la cantidad de casillas indicadas en cantidad bombas de forma aleatoria dentro del rango
        template <class Celda>  
        void bombardearCeldas(Tablero<Celda> &,int x, int y, int z);

        //Devuelve un reporte que indica si se alcanzo a un objetivo contrario y donde
        template <class Celda>  
        void obtenerReporte(Tablero<Celda> &, int x, int y, int z);

        //Inactiva la casilla impactada
        template <class Celda>  
        void lanzarMisil(Tablero<Celda> &, int x, int y, int z);

        //Omite el turno del jugador continuo
        void activarAtributosJugador(bool &atributoJugador);

        //Imprime el reporte de los efectos de las
        void imprimirReporte(std::string reporte);

        std::string getStringTipoFicha(TipoContenido);
};

#endif