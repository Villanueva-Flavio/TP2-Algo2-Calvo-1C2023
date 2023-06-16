#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "./Headers/Tablero.h"
#include "./Headers/Renderizador.h"
#include "./Headers/Jugador.h"
#include "./Headers/BatallaDigital.h"

using namespace std;
struct Niveles{int suelo,mar;};

/* void procesarCambiosMapa(Tablero<Celda*>* tablero, int size) {
    Coordenada imgSize = {size*100, size*70};
    BMP imagen;
    imagen.SetSize(imgSize.x,imgSize.y);
    imprimirBMP(imgSize,&imagen,tablero, getMap());
    imagen.WriteToFile("Partida.bmp");
} */

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