#ifndef __BATALLA_DIGITAL_H__
#define __BATALLA_DIGITAL_H__
#include "Tablero.h"
#include "Celda.h"
#include "Jugador.h"
#include "Structs/Coordenadas.h"

typedef Tablero<Celda*> Mapa;
typedef Lista<Jugador*> Jugadores;
typedef std::map<int, TipoCarta> mapaIndiceDeCartas;

class BatallaDigital{
    private:
        Mapa* mapa;
        Jugadores* jugadores;
        string tipoMapa;
        int cantidadJugadores;
        int turno;
        std::string tipoMapa;
        bool omitirTurno;
        void cargarMapaEspecificado(int aux);
        void mostrarFichasActuales(int jugador);
        void solicitarFichaAMover(int* indice, int jugador);
        void moverFicha(int indice, int jugador);
        void seleccionDeFicha(int jugador);
        bool sePuedeMover(Coordenada coordenada, int jugador);
        void seleccionarDireccion(Coordenada* coordenada);
        void contarEscalado(Coordenada* coordenada);
        void aplicarGravedad(Coordenada* coordenada);
        void explotarMina(Coordenada coordenada);
        
    public:
        //Pre:
        //Post:
        BatallaDigital(int cantidad);
        
        //Pre:
        //Post:
        ~BatallaDigital();

        //Pre:
        //Post:
        void consultarNombres();

        //Pre:
        //Post:
        void cargarJuego();       
    private:
        //Pre:
        //Post:
        std::string consultarTipoDeMapa();

        //Pre:
        //Post:
        void cargarMapas();

        //Pre:
        //Post:
        void cargarCantidadesDeFichasAJugadores();
        
        //----------------- Cargas del mapa--------------

        //Pre:
        //Post:
        void cargarTerrenoPlano(int tipo);

        //Pre:
        //Post:
        void cargarPlaya(int tipo);

        //Pre:
        //Post:
        void cargarRioLago(int tipo);

        //Pre:
        //Post:
        bool esOrilla(int tipo, Coordenada pos);

        // ----------Cargas de las fichas en el mapa------

        //Pre:
        //Post:
        void cargarFichas();

        //Pre:
        //Post:
        void cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner);

        //Pre:
        //Post:
        bool validarCeldaAInsertarFicha(Coordenada* cordenada, TipoContenido tipoDeFicha);

        // ----------Cambio de turno ------

        //Pre:  
        //Post: controla los turnos de cada uno de loos jugadores y salta a alguno en caso de que su turno se tenga que omitir
        void cambiarTurno();

        //Pre: las Coordenada ingresadas deben estar en rango
        //Post: almacena la coordenada de la celda a la que se quiere mover el usuario
        Coordenada obtenerCoordenadaCelda();
        
        //Pre: no tiene
        //Post: devuelve de forma aleatoria un tipo de Carta
        Carta* generarCarta();

        //Pre: no tiene
        //Post: devuelve un mapa con los tipos de cartas existentes
        mapaIndiceDeCartas getMapaIndiceDeCartas();

        //Pre: recibe un puntero a una carta
        //Post: dependiendo del tipo de carta ejecuta la accion correspondiente
        void ejecutarCartaElegida(Carta* carta, Jugador* jugador, Coordenada coordenada);

        //Pre:recibe la coordenada de una celda
        //Post: valida el contenido de la celda seleccionada e inserta la mina si la casilla se encuentra vacia
        //en caso contrario deja vacia la ficha e inactiva la celda
        void insertarMina(Coordenada coordenada);

        //Pre:recibe el indice de iteracion que recorrer una lista
        //Post: reinicia el recorrido de la lista cuando se llega al limite de elementos
        void mantenerIndiceEnRango(int &indice);

        //Pre:recibe el jugador de turno y la coordenada que selecciono el usuario
        //Post:se genera una carta al azar y le da la opcion al usuario de usarla o no
        void tomarCartaDeMazo(Jugador* jugador, Coordenada coordenada);

        //Pre:recibe el jugador de turno y la coordenada que selecciono el usuario
        //Post:se genera una carta al azar y le da la opcion al usuario de usarla o no
        bool mensajeValido(std::string mensaje);

        //------------ Interacciones entre fichas -------------------

        //Pre:recibe la celda dell jugador actual y la celda a la que desea trasladarse
        //Post: Devuelve un string que inidicara el evento que se debe desencadenar dependiendo del tipo de ficha 
        std::string validarContenidoFicha(Celda* celdaJugador, Celda* celdaElegida);

        //Pre:Recibe una celda que contiene una ficha del tipo armamento
        //Post: Devuelve un string que inidicara el evento que se debe desencadenar dependiendo del tipo de ficha 
        std::string validacionArmamento(Celda* celdaJugador, Celda* celdaElegida);

        //Pre:Recibe una celda que contiene una ficha del tipo soldado
        //Post: Devuelve un string que inidicara el evento que se debe desencadenar dependiendo del tipo de ficha 
        std::string validacionSoldado(Celda* celdaJugador, Celda* celdaElegida);

        //Pre:recibe el contenido de una ficha
        //Post:devuelve true si la ficha es armamento y false de caso contrario 
        bool esArmamento(TipoContenido contenidoFicha);

        //Pre:recibe como parametro dos celdas 
        //Post: evalua si las fichas contenidas pertenecen al mismo jugador, devuelve true en caso de que lo sean, y false en caso contrario
        bool esFichaDelJugadorActual(Celda* celdaJugador, Celda* celdaElegida);

        //Pre: recibe el estado de la validacion
        //Post: devuelve una alarte por consola al ussuario para que solucione el error
        void errorEnCeldaElegida(std::string resultado);

        //Pre: recibe las celdas en donde se encuentra la ficha del jugador y la celda ea d donde deseaba moverse
        //Post: elimina la ficha del jugador e inactiva la celda en donde se produjo el encuentro
        void destruirFicha(Ficha* ficha);

        //Pre: recibe como parametro la celda que se desea inactivar
        //Post: inactiva la celda pasada por una cantidad definida de partidas
        void inactivarCelda(Celda* celda);

};
#endif