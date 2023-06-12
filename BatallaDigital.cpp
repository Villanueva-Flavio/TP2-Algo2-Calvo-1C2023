#include <map>
#include <string>
#include "Headers/Tablero.h"
#include "Headers/Celda.h"
#include "Headers/Carta.h"
#include "Headers/Renderizador.h"
#include "Headers/BatallaDigital.h"

using namespace std;

enum Color {PASTO, TIERRA, ARENA, MINA, FUEGO, AGUA, AIRE, SIN_COLOR};

typedef map<string, Coordenada> MapaCoordenadas;
typedef map<Color, RGBApixel> MapaColores;

MapaCoordenadas getMapaCoordenadas(){
    MapaCoordenadas mapa;
    mapa["w"] = {0,0,1};
    mapa["a"] = {-1,0,0};
    mapa["s"] = {0,0,-1};
    mapa["d"] = {1,0,0};
    mapa["W"] = {0,0,1};
    mapa["A"] = {-1,0,0};
    mapa["S"] = {0,0,-1};
    mapa["D"] = {1,0,0};
    return mapa;
};

BatallaDigital::BatallaDigital(int cantidad){
    this->mapa = new Mapa(cantidad*4, cantidad*4, cantidad*4);
    this->jugadores = new Jugadores();
    for(int i = 0; i < cantidad; i++){
        Jugador* jugador = new Jugador();
        this->jugadores->add(jugador);
    }
    this->cantidadJugadores = cantidad;
    this->turno = 0;
}

BatallaDigital::~BatallaDigital(){
    delete this->mapa;
    delete this->jugadores;
}

// Pide el nombres para cada jugador
void BatallaDigital::consultarNombres(){
    for (int i = 0; i < this->cantidadJugadores; i++) {
        bool nombreValido = false;
        while (!nombreValido) {
            string nombre;
            cout << "\nIngrese el nombre del jugador " << i + 1 << ": ";
            cin >> nombre;
            this->jugadores->getLData(i)->setNombre(nombre);

            if (this->jugadores->getLData(i)->getNombre() != "") {
                nombreValido = true;
            }
        }
    }
}

// Pide el tipo de mapa que se usara
void BatallaDigital::consultarTipoDeMapa(string tipoMapa){

    cout << "\nSeleccione un tipo de mapa. (playa - mar - tierra - desierto - rio - lago)\n(escriba su respuesta): ";
    cin >> this->tipoMapa;

    while(this->tipoMapa != "playa" && this->tipoMapa != "mar" && this->tipoMapa != "tierra" && this->tipoMapa != "desierto" && this->tipoMapa != "rio" && this->tipoMapa != "lago"){
        cout << "\nNo se ingrese un tipo de mapa valido.\nSeleccione un tipo de mapa. (playa - mar - tierra - desierto - rio - lago)\n(escriba su respuesta): ";
        cin >> this->tipoMapa;
    }
}

void BatallaDigital::consultarColores(){
    RGBApixel colorElegido;

    for (int i = 0; i < this->cantidadJugadores; i++) {
        cout << "Ingrese el color del jugador " << i + 1 << " (ingresar 3 valores entre 0 y 255 inclusive): ";
        cin >> colorElegido.Red >> colorElegido.Green >> colorElegido.Blue;
        
        while(colorElegido.Red < 0 || colorElegido.Red > 255 || colorElegido.Green < 0 || colorElegido.Green > 255 || colorElegido.Blue < 0 || colorElegido.Blue > 255){
            cout << "Ingrese un color valido (ingresar 3 valores entre 0 y 255 inclusive): ";
            cin >> colorElegido.Red >> colorElegido.Green >> colorElegido.Blue;
        }
    this->jugadores->getLData(i)->setColor(colorElegido);
    }
}

int jugadoresConFichas(){
    
}

void BatallaDigital::cargarJuego(){
    consultarNombres();
    consultarColores();

    consultarTipoDeMapa(tipoMapa);  // se uso string
    //Cargar tipo mapa | enum tipo
    //Posicionar fichas  | enum tipo
}

void BatallaDigital::ejecutarTurno(){
    for(int i = 0; i < this->cantidadJugadores; i++){
        
        //Si jugador no tiene fichas -> no juega
        //Si jugador tiene turno omitido -> no juega
        
        //Print Mapa_Jugador_X.bmp

        //Pedir Ficha a mover - Mostrar ficha
        //Pedir movimiento o accion
        //Ejecutar movimiento o accion

        //Soltar mina
        //Comprobar si explota

        //Robar Carta    

    }
}

void BatallaDigital::jugar(){
    while(this->jugadoresConFichas() > 1){
        this->ejecutarTurno();
    }
    //mensajeVictoria(this->jugadores->getJugador(0)->getNombre()); (Podria quedar para main)
}
