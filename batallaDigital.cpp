#include <map>
#include <string>
#include "Headers/Tablero.h"
#include "Headers/Celda.h"
#include "Headers/Carta.h"
#include "Headers/Renderizador.h"

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

int BatallaDigital::jugadoresVivos(){
    int vivos = 0, sol = 0, arm = 0;
    for (int i = 0; i < this->cantidadJugadores; i++) {
        sol = this->jugadores->getLData(i)->getSoldados();
        arm = this->jugadores->getLData(i)->getArmamentos();
        vivos = (sol != 0 && arm != 0)? vivos +1 : vivos;
    }
    return vivos;
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
        /* Cambio Turno {
            if ! Omitir turno 
                seleccionar ficha
                mover ficha
                ejecutar cambio
                mostrar foto nueva
                soltar mina
                if(barco)
                    soltar mina
                robar carta
            !omitirTurno
            turno ++
} */

    }

    /* 

reordenar map movimientos para yenny
reordenar map colores (flavio hace bitmap)

mensaje victoria

arreglar cantidad generada de fichas

hacer que el jugador solo vea sus fichas

movimiento vertical R-F

Carta lista

upper cargar mapas */
}

void BatallaDigital::jugar(){
    
    while(jugadoresVivos() > 1){
        this->ejecutarTurno();
    }
    //mensajeVictoria(this->jugadores->getJugador(0)->getNombre()); (Podria quedar para main)


}

    