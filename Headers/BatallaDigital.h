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
        bool sePuedeMover(Coordenada coordenada, int jugador);

        //POST: Le pide al usuario que ingrese una direccion, y aplica el cambio de coordenada
        void seleccionarDireccion(Coordenada* coordenada);

        //PRE: 'coordenada' debe estar inicializada
        //POST: valida si la coordenada ingresada este dentro del rango permitido, de lo contrario solicita de vuelta una direccion
        void procesarDireccion(Coordenada* coordenada);

        //PRE: 'coordenada' debe contener un valor valido
        //POST: Aplica escalar un punto si se choca con terreno en subida
        void contarEscalado(Coordenada* coordenada);

        //PRE: 'coordenada' debe estar inicializada
        //POST: Aplica gravedad si se choca con terreno en bajada
        void aplicarGravedad(Coordenada* coordenada);

        //PRE: 'c1' y 'c2' deben estar inicializadas
        //POST: remueve las fichas de las coordenadas recibidas
        void removerAmbasFichas(Coordenada c1, Coordenada c2);

        //PRE: 'jugador' y 'coordenada' deben contener un valor valido
        //Post: Gestiona el movimiento de la ficha
        void aplicarMovimiento(int jugador, Coordenada* coordenada);

        //PRE: 'evento' debe estar inicializado, c1 y c2 deben contener valores validos
        //POST: Gestiona el evento de colision entre fichas (En la que al menos una muere)
        void eventoColisionMortal(std::string evento, Coordenada c1, Coordenada c2);

        //PRE: c1 y c2 deben contener valores validos
        //POST: Gestiona el cambio de posicion de la ficha a la siguiente coordenada
        void eventoDesplazamiento(Coordenada c1, Coordenada c2);

        //PRE: 'coordenada' y 'jugador' deben contener valores validos
        //POST: Gestiona el evento correspondiente al movimiento de la ficha
        void procesarEventos(Coordenada coordenada, int jugador);

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


    public:
        BatallaDigital(int cantidad);
        
        ~BatallaDigital();
        void cargarJuego();
        void consultarNombres();
        void consultarTipoDeMapa(string tipoMapa);
        void consultarColores();
        int jugadoresVivos();

};
#endif