#include <string>
#include "Tablero.h"
#include "Celda.h"
#include "Enums.h"
#include "Coordenadas.h"
#include <map>

#ifndef __CARTA_H__
#define __CARTA_H__

class Carta{
    private:

        TipoCarta carta;
        bool cartaActiva;
        int radioAccion;
        int cantidadBombas;

    public:

        //Post: construye una instancia de la clase carta
        Carta(TipoCarta carta);

        //Pre: recibe como parametro el tablero y el centro de accion
        //Post:Dependiendo del tipo de carta desencadenara la accion de bombardear la zona, enviar un reporte al jugador o lanzar un ataque quimico
        void usarCarta(Tablero<Celda*>* tablero, Coordenada centro);

        //Post:Permite saber cual es el tipo de carta
        TipoCarta getTipoCarta();

        //Post:devuelve un strung del tipo de carta
        std::string getStringTipoCarta();

        //Post:Permite saber si la carta esta activa
        bool getCartaActiva();

    private:
        //Pre: la carta debe ser del tipo ataque quimico, se recibe una tablero y las Coordenada de la celda que se quiere inactivar
       //Post: Se inactivan las celdas del perimetro marcado por un radio de 5 casillas
        void inactivarCeldas(Tablero<Celda*>* tablero,Coordenada centro);

        //Pre:la carta debe ser del tipo bombardeo, se recibe una tablero y las Coordenada de la celda que se quiere inactivar
        //Post: Inactiva la cantidad de casillas indicadas en cantidad bombas de forma aleatoria dentro del radio de 3 casillas
        void bombardearCeldas(Tablero<Celda*>* tablero,Coordenada centro);

        //Pre:la carta debe ser del tipo avion, se recibe una tablero y las Coordenada de la celda que se quiere inactivar
        //Post:Devuelve un reporte con el contenido de las fichas que se encuentran a una distancia de 8 casillas del punto del centro
        void obtenerReporte(Tablero<Celda*>* tablero, Coordenada centro);

        //Pre:la carta debe ser del tipo barco_misil, se recibe una tablero y las Coordenada de la celda que se quiere inactivar
        //Post:inactiva la celda especificada en la coordenada enviada 
        void lanzarMisil(Tablero<Celda*>* tablero, Coordenada centro);

        //Pre:recibe un reporte
        //Post:devuelve un resumen de la jugada descriubiendo las Coordenada, el jugador y el contenido en caso de haber una ficha, en caso
        //de no haber alcanzado a ninguna ficha con la jugada devolvera un mensaje comunicando que no se encontro nada en la zona
        void imprimirReporte(std::string reporte);

        //Pre: recibe el contenido de una ficha
        //Post: devuelve un string  que describa el tipo de contenido
        std::string getStringTipoFicha(TipoContenido tipoFicha);

        //Pre:recibe las Coordenada de centro y el punto 
        //Post:Devuelve la cantidad de turnos que va a permanecer la casilla dependiendo de la distancia a la que se encuentre el punto del centro de la explosion
        int getTurnosInactiva(Coordenada centro, Coordenada punto);

        //Pre: recibe un tablero y las Coordenadad de la celda 
        //Post: inactiva las celdas pasadas por coordenada
        void inactivarCelda(Tablero<Celda*>* tablero, Coordenada punto, int turnosInactiva);
        
};

#endif