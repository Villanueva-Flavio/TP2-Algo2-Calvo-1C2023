#ifndef __BATALLA_DIGITAL_H__
#define __BATALLA_DIGITAL_H__
#include "Tablero.h"
#include "Celda.h"
#include "Jugador.h"
#include "Structs/Coordenadas.h"
#include "./Enums.h"
#include "../CoordenadasNew.h"

class BatallaDigital{
    private:
        Tablero<Celda*>* mapa;
        Lista<Jugador*>* jugadores;
        std::string tipoMapa;
        int cantidadJugadores;
        int turno;
        bool omitirTurno;

    public:
        BatallaDigital(int cantidad);
        
        ~BatallaDigital();

        //Post: Gestiona la carga del mapa y sus respectivas fichas
        void cargarJuego();      

        //Post: controla los turnos de cada uno de loos jugadores y salta a alguno en caso de que su turno se tenga que omitir
        void jugar();

    private:

        //PRE: el nombre del mapa pasado 'aux' no puede ser NULL y debe contener un valor valido
        //POST: carga el mapa en el tablero
        void cargarMapaEspecificado(std::string aux);

        //PRE: 'jugador' debe contener un valor valido
        //POST: muetsra por pantalla las fichas que tiene el jugador
        void mostrarFichasActuales(int jugador);

        //PRE: 'jugador' debe contener un valor valido
        //POST: solicita al usuario que ingrese el indice de la ficha que desea mover
        void solicitarFichaAMover(int* indice, int jugador);

        //PRE: 'indice' y 'jugador' deben contener un valor valido
        //POST: solicita al usuario que ingrese el indice de la ficha que desea mover
        void moverFicha(int indice, int jugador);

        //PRE: 'coordenada' y 'jugador' deben estar inicializados
        //POST: Devuelve true si la coordenada es valida para mover la ficha
        bool sePuedeMover(CoordenadaNew coordenada, int jugador);

        //PRE: 'direccion' debe ser valida
        //POST: devuelve la coordenada con la direccion a la que se desea mover la ficha
        CoordenadaNew obtenerCoordenadaDireccion(std::string direccion);

        //Pre:recibe una direccion
        //Post: devuelve true si es valida o false en caso contrario
        bool direccionValida(std::string direccion);

        //POST: Le pide al usuario que ingrese una direccion, y aplica el cambio de coordenada
        void seleccionarDireccion(CoordenadaNew* coordenada);

        //PRE: 'coordenada' debe estar inicializada
        //POST: valida si la coordenada ingresada este dentro del rango permitido, de lo contrario solicita de vuelta una direccion
        void procesarDireccion(CoordenadaNew* coordenada);

        //PRE: 'coordenada' debe contener un valor valido
        //POST: Aplica escalar un punto si se choca con terreno en subida
        void contarEscalado(CoordenadaNew* coordenada);

        //PRE: 'coordenada' debe estar inicializada
        //POST: Aplica gravedad si se choca con terreno en bajada
        void aplicarGravedad(CoordenadaNew* coordenada);

        //PRE: 'c1' y 'c2' deben estar inicializadas
        //POST: remueve las fichas de las coordenadas recibidas
        void removerAmbasFichas(CoordenadaNew c1, CoordenadaNew c2);

        //PRE: 'jugador' y 'coordenada' deben contener un valor valido
        //Post: Gestiona el movimiento de la ficha
        void aplicarMovimiento(int jugador, CoordenadaNew* coordenada);

        //PRE: 'evento' debe estar inicializado, c1 y c2 deben contener valores validos
        //POST: Gestiona el evento de colision entre fichas (En la que al menos una muere)
        void eventoColisionMortal(std::string evento, CoordenadaNew c1, CoordenadaNew c2);

        //PRE: c1 y c2 deben contener valores validos
        //POST: Gestiona el cambio de posicion de la ficha a la siguiente coordenada
        void eventoDesplazamiento(CoordenadaNew c1, CoordenadaNew c2);

        //PRE: 'coordenada' y 'jugador' deben contener valores validos
        //POST: Gestiona el evento correspondiente al movimiento de la ficha
        void procesarEventos(CoordenadaNew coordenada, int jugador);

        //PRE: 'jugador' debe contener un valor valido
        //POST: Gestiona la interaccion del jugador en seleccionar la ficha y moverla
        void jugarFicha(int jugador);

        //POST: Devuelve la cantidad de jugadores que poseen fichas vivas
        int jugadoresConFichasVivas();

        //PRE: 'jugador' debe contener un valor valido
        //POST: Devuelve true si el jugador tiene fichas vivas
        bool jugadorConFichasVivas(int jugador);

        //POST: Reduce 1 turno restante de inactiva a las celdas inactivas existentes
        void procesarInactivas();

        //POST: Emite un mensaje de Empate a la consola
        void mensajeEmpate();

        //PRE: 'jugador' debe contener un valor valido
        //POST: Saca una foto del mapa en 3 angulos distintos, con las fichas del jugador seleccionado
        void sacarFoto(int jugador);

        //Post: Devuelve el tipo de mapa en string
        std::string consultarTipoDeMapa();

        //Post: Consulta el tipo de mapa y lo carga
        void cargarMapas();

        //Post: Carga la cantidad de fichas a cada jugador
        void cargarCantidadesDeFichasAJugadores();
        
        //----------------- Cargas del mapa--------------

        //Pre: 'tipo' debe contener un valor valido
        //Post: Carga el mapa especificado
        void cargarTerrenoPlano(std::string tipo);

        //Post: Carga el mapa especificado
        void cargarPlaya(std::string tipo);

        //Post: Carga el mapa especificado
        void cargarRioLago(std::string tipo);

        //Pre: 'tipo' y 'pos' deben contener valores validos
        //Post: Devuelve True si es parte de la orilla de un lago o rio
        bool esOrilla(std::string tipo, CoordenadaNew pos);

        // ----------Cargas de las fichas en el mapa------

        //Post: Carga las fichas de los jugadores
        void cargarFichas();

        //Pre: 'cantidadDeCarga', 'tipoDeFicha' y 'jugadorOwner' deben contener valores validos
        //Post: Carga la ficha en el mapa
        void cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner);

        //Pre: 'coordenada' debe contener un valor valido y 'tipoDeFicha' debe estar inicializado
        //Post: Devuelve true si la celda esta vacia y se puede insertar la ficha
        bool validarCeldaAInsertarFicha(CoordenadaNew cordenada, TipoContenido tipoDeFicha);

        // ----------Cambio de turno ------

        //Post: almacena la coordenada de la celda a la que se quiere mover el usuario
        CoordenadaNew obtenerCoordenadaCelda();
        
        //Post: devuelve de forma aleatoria un tipo de Carta
        Carta* generarCarta();

        //Post: devuelve el tipo de carta dependiendo del indice que reciba
        TipoCarta obtenerTipoDeCarta(int indiceDeCarta);

        //Pre: 'carta', 'jugador' y 'coordenada' deben contener un valor valido
        //Post: dependiendo del tipo de carta ejecuta la accion correspondiente
        void ejecutarCartaElegida(Carta* carta, Jugador* jugador, CoordenadaNew coordenada);
        
        //Pre: 'coordenada' debe contener un valor valido
        //Post: valida el contenido de la celda seleccionada e inserta la mina si la casilla se encuentra vacia
        //en caso contrario deja vacia la ficha e inactiva la celda
        void insertarMina(CoordenadaNew coordenada);

        //Post: reinicia el recorrido de la lista cuando se llega al limite de elementos
        void mantenerIndiceEnRango(int &indice);

        //Pre: 'jugador' y 'coordenada' deben contener un valor valido
        //Post:se genera una carta al azar y le da la opcion al usuario de usarla o no
        void tomarCartaDeMazo(Jugador* jugador, CoordenadaNew coordenada);

        //Pre: 'mensaje' debe estar inicializado
        //Post: se genera una carta al azar y le da la opcion al usuario de usarla o no
        bool mensajeValido(std::string mensaje);

        //Pre: 'jugador' debe contener un valor valido
        //Post: devuelve el indice de la carta solictado por el usuario
        int obtenerIndiceDeCarta(Jugador* jugador);

        //Pre: 'coordenada' debe contener un valor valido
        //Post: devuelve el indice de la carta solictado por el usuario
        bool coordenadaEnRango(CoordenadaNew coordenada);

        //Pre: 'indiceDeJugador' debe contener un valor valido
        //Post: devuelve el indice de la carta solictado por el usuario
        void moverFicha(int indiceDeJugador);

        //------------ Interacciones entre fichas -------------------

        //Pre: 'celdaJugador' y 'celdaElegida' deben contener un valor valido
        //Post: Devuelve un string que inidicara el evento que se debe desencadenar dependiendo del tipo de ficha 
        std::string validarContenidoFicha(Celda* celdaJugador, Celda* celdaElegida);

        //Pre: 'celdaJugador' y 'celdaElegida' deben contener un valor valido
        //Post: Devuelve un string que inidicara el evento que se debe desencadenar dependiendo del tipo de ficha 
        std::string validacionArmamento(Celda* celdaJugador, Celda* celdaElegida);

        //Pre: 'celdaJugador' y 'celdaElegida' deben contener un valor valido
        //Post: Devuelve un string que inidicara el evento que se debe desencadenar dependiendo del tipo de ficha 
        std::string validacionSoldado(Celda* celdaJugador, Celda* celdaElegida);

        //Pre: 'contenidoFicha' debe contener un valor valido
        //Post:devuelve true si la ficha es armamento y false de caso contrario 
        bool esArmamento(TipoContenido contenidoFicha);

        //Pre: 'celdaJugador' y 'celdaElegida' deben contener un valor valido
        //Post: evalua si las fichas contenidas pertenecen al mismo jugador, devuelve true en caso de que lo sean, y false en caso contrario
        bool esFichaDelJugadorActual(Celda* celdaJugador, Celda* celdaElegida);

        //Pre: 'resultado' debe contener un valor valido
        //Post: devuelve una alarte por consola al ussuario para que solucione el error
        void errorEnCeldaElegida(std::string resultado);

        //Post: elimina la ficha del jugador e inactiva la celda en donde se produjo el encuentro
        void destruirFicha(Ficha* ficha);

        //Post: inactiva la celda pasada por una cantidad definida de partidas
        void inactivarCelda(Celda* celda);

};
#endif