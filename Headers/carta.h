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

    public:

        //Post: construye una instancia de la clase carta
        Carta(TipoCarta carta);

        //Pre: recibe como parametro un atributo booleado
        //Post:Dependiendo del tipo de carta desencadenara la accion de inactivar a un jugador o el de proteger todas sus fichas
        void usarCarta(bool &atributoJugador);

        //Pre: recibe como parametro el tablero y el centro de accion
        //Post:Dependiendo del tipo de carta desencadenara la accion de bombardear la zona, enviar un reporte al jugador o lanzar un ataque quimico
        void usarCarta(Tablero<Celda*>* tablero, coordenadas centro);

        //Post:Permite saber cual es el tipo de carta
        TipoCarta getTipoCarta();

        //Post:Permite saber si la carta esta activa
        bool getCartaActiva();

    private:
        //Pre: la carta debe ser del tipo ataque quimico, se recibe una tablero y las coordenadas de la celda que se quiere inactivar
       //Post: Se inactivan las celdas del perimetro marcado por un radio de 5 casillas
        void inactivarCeldas(Tablero<Celda*>* tablero,coordenadas centro);

        //Pre:la carta debe ser del tipo bombardeo, se recibe una tablero y las coordenadas de la celda que se quiere inactivar
        //Post: Inactiva la cantidad de casillas indicadas en cantidad bombas de forma aleatoria dentro del radio de 3 casillas
        void bombardearCeldas(Tablero<Celda*>* tablero,coordenadas centro);

        //Pre:la carta debe ser del tipo avion, se recibe una tablero y las coordenadas de la celda que se quiere inactivar
        //Post:Devuelve un reporte con el contenido de las fichas que se encuentran a una distancia de 8 casillas del punto del centro
        void obtenerReporte(Tablero<Celda*>* tablero, coordenadas centro);

        //Pre:la carta debe ser del tipo barco_misil, se recibe una tablero y las coordenadas de la celda que se quiere inactivar
        //Post:inactiva la celda especificada en la coordenada enviada 
        void lanzarMisil(Tablero<Celda*>* tablero, coordenadas centro);

        //Pre: la carta debe ser del tipo omision y debe recibir una referencia del estado del siguiente jugador que se encuentre activo 
        //Post: lo inactiva por una ronda
        void activarAtributosJugador(bool &atributoJugador);

        //Pre:recibe un reporte
        //Post:devuelve un resumen de la jugada descriubiendo las coordenadas, el jugador y el contenido en caso de haber una ficha, en caso
        //de no haber alcanzado a ninguna ficha con la jugada devolvera un mensaje comunicando que no se encontro nada en la zona
        void imprimirReporte(std::string reporte);

        //Pre: recibe el contenido de una ficha
        //Post: devuelve un string  que describa el tipo de contenido
        std::string getStringTipoFicha(TipoContenido tipoFicha);

        //Pre:recibe las coordenadas de centro y el punto 
        //Post:Devuelve la cantidad de turnos que va a permanecer la casilla dependiendo de la distancia a la que se encuentre el punto del centro de la explosion
        int getTurnosInactiva(coordenadas centro, coordenadas punto);

        //Pre: recibe un tablero y las coordenadasd de la celda 
        //Post: inactiva las celdas pasadas por coordenada
        void inactivarCelda(Tablero<Celda*>* tablero, coordenadas punto, int turnosInactiva);

        //Post: devuleve un map de los tipos de cartas
        mapaTiposDeCartas getMapaTipoDeCartas();

        //Post: devuleve un map de los tipos de contenido de las fichas
        mapaTiposContenido getMapaTiposContenido();
        
};

#endif