#ifndef __BATALLA_DIGITAL_H__
#define __BATALLA_DIGITAL_H__
#include "Tablero.h"
#include "Celda.h"
#include "Jugador.h"

typedef Tablero<Celda*> Mapa;
typedef Lista<Jugador*> Jugadores;

class BatallaDigital{
    private:
        Mapa* mapa;
        Jugadores* jugadores;
        int cantidadJugadores;
        int turno;
        std::string tipoMapa;
    public:
        BatallaDigital(int cantidad);
        ~BatallaDigital();
        void consultarNombres();
        void cargarJuego();       
    private:
        std::string consultarTipoDeMapa();
        void cargarMapas();
        void cargarCantidadesDeFichasAJugadores();
        // Cargas del mapa
        void cargarTerrenoPlano(int tipo);
        void cargarPlaya(int tipo);
        void cargarRioLago(int tipo);
        bool esOrilla(int tipo, Coordenada pos);
        // Cargas de las fichas en el mapa
        void cargarFichas();
        void cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner);
        bool validarCeldaAInsertarFicha(Coordenada* cordenada, TipoContenido tipoDeFicha);
};
#endif