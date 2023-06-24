#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Tablero.h"
#include "Renderizador.h"
#include "Jugador.h"
#include "BatallaDigital.h"

using namespace std;

void solicitarJugadores(int* cantJugadores){
    cout << "+-----------------------------------+\n";
    cout << "|          Batalla Digital          |\n";
    cout << "+-----------------------------------+\n";
    cout << "|                                   |\n";
    cout << "|        Presione una tecla         |\n";
    cout << "|          para comenzar...         |\n";
    cout << "|                                   |\n";
    cout << "+-----------------------------------+\n";
    cin.get();

    cout << "Ingrese la cantidad de jugadores: ";
    cin >> *cantJugadores;
    while(*cantJugadores < 2 || *cantJugadores > 10){
        cout << "La cantidad de jugadores debe estar entre 2 y 10. Ingrese nuevamente: ";
        cin >> *cantJugadores;
    }
}

int main(){
    srand(time(NULL));
    int cantJugadores;
    solicitarJugadores(&cantJugadores);
    BatallaDigital* Juego = new BatallaDigital(cantJugadores);
    Juego->cargarJuego();
    Juego->jugar();
    return 0;
}