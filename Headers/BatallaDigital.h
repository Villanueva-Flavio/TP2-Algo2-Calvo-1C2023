#ifndef __BATALLA_DIGITAL_H__
#define __BATALLA_DIGITAL_H__
#include "Tablero.h"
#include "Celda.h"
#include "Jugador.h"
#include "Structs/Coordenadas.h"
#include "./Enums.h"

typedef Tablero<Celda*> Mapa;
typedef Lista<Jugador*> Jugadores;
typedef std::map<int, TipoCarta> mapaIndiceDeCartas;

class BatallaDigital{
    private:
        Mapa* mapa;
        Jugadores* jugadores;
        std::string tipoMapa;
        int cantidadJugadores;
        int turno;
        bool omitirTurno;
        

        //PRE: recibe un string con el nombre del archivo
        //POST: carga el mapa en el tablero
        void cargarMapaEspecificado(std::string aux);

        //PRE: recibe un int con el indice dle jugador
        //POST: Muetsra por pantalla las fichas que tiene el jugador
        void mostrarFichasActuales(int jugador);

        //PRE: recibe un int puntero del indice de ficha y con el indice del jugador
        //POST: solicita al usuario que ingrese el indice de la ficha que desea mover
        void solicitarFichaAMover(int* indice, int jugador);

        //PRE: recibe un int del indice de ficha y con el indice del jugador
        //POST: solicita al usuario que ingrese el indice de la ficha que desea mover
        void moverFicha(int indice, int jugador);

        //PRE: Recibe una Coordenada y el indice de jugador
        //POST: Devuelve true si la coordenada es valida para mover la ficha
        bool sePuedeMover(Coordenada coordenada, int jugador);

        //PRE: Recibe una Coordenada puntero
        //POST: Le pide al usuario que ingrese una direccion, y aplica el cambio de coordenada
        void seleccionarDireccion(Coordenada* coordenada);

        //PRE: recibe un puntero a una coordenada
        //POST: Aplica escalar un punto si se choca con terreno en subida
        void contarEscalado(Coordenada* coordenada);

        //PRE: Recibe un puntero a una coordenada
        //POST: Aplica gravedad si se choca con terreno en bajada
        void aplicarGravedad(Coordenada* coordenada);

        //PRE: Recibe 2 coordenadas
        //POST: remueve las fichas de las coordenadas recibidas
        void removerAmbasFichas(Coordenada c1, Coordenada c2);

        //PRE: Recibe el indice de jugador y un puntero a coordenada
        //Post: Gestiona el movimiento de la ficha
        void aplicarMovimiento(int jugador, Coordenada* coordenada);

        //PRE: Recibe un string de evento y 2 coordenadas (Fuente y destino)
        //POST: Gestiona el evento de colision entre fichas (En la que al menos una muere)
        void eventoColisionMortal(std::string evento, Coordenada c1, Coordenada c2);

        //PRE: Recibe 2 coordenadas (Fuente y Destino)
        //POST: Gestiona el cambio de posicion de la ficha a la siguiente coordenada
        void eventoDesplazamiento(Coordenada c1, Coordenada c2);

        //PRE: Recibe una coordenada y el indice de jugador
        //POST: Gestiona el evento correspondiente al movimiento de la ficha
        void procesarEventos(Coordenada coordenada, int jugador);

        //PRE: Recibe un int del indice de jugador
        //POST: Gestiona la interaccion del jugador en seleccionar la ficha y moverla
        void jugarFicha(int jugador);

        //POST: Devuelve la cantidad de jugadores que poseen fichas vivas
        int jugadoresConFichasVivas();

        //PRE: Recibe un int del indice de jugador
        //POST: Devuelve true si el jugador tiene fichas vivas
        bool jugadorConFichasVivas(int jugador);

        //POST: Reduce 1 turno restante de inactiva a las celdas inactivas existentes
        void procesarInactivas();

        //POST: Emite un mensaje de Empate a la consola
        void mensajeEmpate();

        //PRE: Recibe un int del indice de jugador
        //POST: Saca una foto del mapa en 3 angulos distintos, con las fichas del jugador seleccionado
        void sacarFoto(int jugador);


    public:
        BatallaDigital(int cantidad);
        
        ~BatallaDigital();

        //Post: Consulta a todos los jugadores los nombres de usuario
        void consultarNombres();

        //Post: Gestiona la carga del mapa y sus respectivas fichas
        void cargarJuego();      

        //Post: controla los turnos de cada uno de loos jugadores y salta a alguno en caso de que su turno se tenga que omitir
        void jugar();

    private:

        //Post: Devuelve el tipo de mapa en string
        std::string consultarTipoDeMapa();

        //Post: Consulta el tipo de mapa y lo carga
        void cargarMapas();

        //Post: Carga la cantidad de fichas a cada jugador
        void cargarCantidadesDeFichasAJugadores();
        
        //----------------- Cargas del mapa--------------

        //Pre: Recibe un string
        //Post: Carga el mapa especificado
        void cargarTerrenoPlano(std::string tipo);

        //Pre: Recibe un string
        //Post: Carga el mapa especificado
        void cargarPlaya(std::string tipo);

        //Pre: Recibe un string
        //Post: Carga el mapa especificado
        void cargarRioLago(std::string tipo);

        //Pre: Recibe un string y una Coordenada
        //Post: Devuelve True si es parte de la orilla de un lago o rio
        bool esOrilla(std::string tipo, Coordenada pos);

        // ----------Cargas de las fichas en el mapa------

        //Post: Carga las fichas de los jugadores
        void cargarFichas();

        //Pre: Recibe un int con la cantidad de carga, un TipoContenido y un int con el indice del jugador
        //Post: Carga la ficha en el mapa
        void cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner);

        //Pre: Recibe una Coordenada y el Tipo de ficha
        //Post: Devuelve true si la celda esta vacia y se puede insertar la ficha
        bool validarCeldaAInsertarFicha(Coordenada cordenada, TipoContenido tipoDeFicha);

        // ----------Cambio de turno ------


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

        //Pre:se tiene que validar que el indice sea valido
        //Post: devuelve el indice de la carta solictado por el usuario
        int obtenerIndiceDeCarta(Jugador* jugador);

        //Pre:se tiene que validar que el indice sea valido
        //Post: devuelve el indice de la carta solictado por el usuario
        bool coordenadaEnRango(Coordenada coordenada);

        //Pre:se tiene que validar que el indice sea valido
        //Post: devuelve el indice de la carta solictado por el usuario
        void moverFicha(int indiceDeJugador);

        //------------ Interacciones entre fichas -------------------

        //Pre:recibe la celda del jugador actual y la celda a la que desea trasladarse
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