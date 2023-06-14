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
    cout << "\n--------------------Batalla Digital--------------------\n\n";
    cin.get();

    cout << "Ingrese la cantidad de jugadores: ";
    cin >> *cantJugadores;
    while(*cantJugadores < 2 || *cantJugadores > 10){
        cout << "La cantidad de jugadores debe ser entre 2 y 10. Ingrese nuevamente: ";
        cin >> *cantJugadores;
    }
}

int main(){
    srand(time(NULL));
    int cantJugadores;
    solicitarJugadores(&cantJugadores);
    BatallaDigital* Juego = new BatallaDigital(cantJugadores);
    Juego->cargarJuego();
    return 0;
}