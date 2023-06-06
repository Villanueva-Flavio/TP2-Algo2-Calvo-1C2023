#ifndef __CARGA_H__
#define __CARGA_H__

#include "./Headers/Tablero.h"
#include "./Headers/Jugador.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

#define CAPA_MAXIMA 5

class Cargar{
    private:

        Tablero<Celda*>* mundoDelJuego;

        Lista<Jugador*>* jugadores;

        int numeroDeJugadores;

        std::string tipoDeMundo;

        std::string** nombres;
    
    public:

        // Recibe el mundo del juego, la lista de jugadores, el tipo de mundo y la lista con nombres
        Cargar(Tablero<Celda*>* mundoDelJuego, Lista<Jugador*>* jugadores, std::string tipoDeMundo, std::string** nombres);

        void cargarJuego();

    private:

        void generarMundo(std::string tipoDeMundo, Tablero<Celda*>* mundoDelJuego);

        void cargarPlaya(Tablero<Celda*>* mundoDelJuego);

        void cargarMar(Tablero<Celda*>* mundoDelJuego);

        void cargarTierra(Tablero<Celda*>* mundoDelJuego);

        void cargarDesierto(Tablero<Celda*>* mundoDelJuego);

        bool noEsOrillaDelLago(Tablero<Celda*>* mapa, int x, int y, int z, int size);

        void cargarLago(Tablero<Celda*>* mundoDelJuego, int size);

        bool noEsOrillaRio(Tablero<Celda*>* mapa, int x, int y, int z, int size);

        void cargarRio(Tablero<Celda*>* mundoDelJuego, int size);

        bool verificarOpcion(std::string tipoDeMundo);

    private:

        void cargarJugadores(Lista<Jugador*>* jugadores,std::string** nombres);

        void cargarNombres(Lista<Jugador*>* jugadores,std::string** nombres);

        void cargarCantidadFichas(Lista<Jugador*>* jugadores);

        void cargarTurnos(Lista<Jugador*>* jugadores);

    private:

        void cargarFichas(Tablero<Celda*>* mundoDelJuego, Lista<Jugador*>* jugadores, std::string tipoMundo);

        int obtenerCantidadesDeFichas(Lista<Jugador*>* jugadores, int tipoDeFichaActual, int jugadorActual);

        int cantidadDistintaDeArmamento(int tipoDeFichaActual);

        bool verificarSolapamientos(Tablero<Celda*>* mundoDelJuego, int tipoDeFichaActual, std::string tipoMundo, int x, int y, int z);

};

#endif