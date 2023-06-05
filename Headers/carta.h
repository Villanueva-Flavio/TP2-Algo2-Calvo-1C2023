#include <string>
#include "Tablero.h"
#include "Celda.h"
#include "Enums.h"
#include "Structs/Coordenadas.h"
#include <map>

#ifndef __CARTA_H__
#define __CARTA_H__

typedef  std::map<int, TipoCarta> mapaTiposDeCartas;
typedef  std::map<int, std::string> mapaTiposContenido;

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
        void usarCarta(Tablero<Celda*>* tablero, coordenadas centro);

        //Permite saber cual es el tipo de carta
        TipoCarta getTipoCarta();

        //Permite saber si la carta esta activa
        bool getCartaActiva();

    private:

        //Se inactivan las celdas del perimetro marcado por el radio
        void inactivarCeldas(Tablero<Celda*>* tablero,coordenadas centro);

        //Inactiva la cantidad de casillas indicadas en cantidad bombas de forma aleatoria dentro del rango
        void bombardearCeldas(Tablero<Celda*>* tablero,coordenadas centro);

        //Devuelve un reporte que indica si se alcanzo a un objetivo contrario y donde 
        void obtenerReporte(Tablero<Celda*>* tablero, coordenadas centro);

        //Inactiva la casilla impactada
        void lanzarMisil(Tablero<Celda*>* tablero, coordenadas centro);

        //Omite el turno del jugador continuo
        void activarAtributosJugador(bool &atributoJugador);

        //Imprime el reporte de los efectos de las
        void imprimirReporte(std::string reporte);

        std::string getStringTipoFicha(TipoContenido tipoFicha);

        //Devuelve la cantidad de turnos que va a permanecer la casilla dependiendo de la distancia a la que se encuentre del centrio de la explosion
        int getTurnosInactiva(coordenadas centro, coordenadas punto);

        //Post: devuleve un map de los tipos de cartas
        mapaTiposDeCartas getMapaTipoDeCartas();

        mapaTiposContenido getMapaTiposContenido();
        
};

#endif