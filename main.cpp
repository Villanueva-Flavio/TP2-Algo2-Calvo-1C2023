#include "./Headers/Tablero.h"
#include "./Headers/Celda.h"
#include "./Headers/Renderizador.h"
#include "./Headers/Jugador.h"
#include "./Headers/DatosIngresados.h"
#include <iostream>
#include <string>
using namespace std;




void procesarMapa(Tablero<Celda*>* tablero, int size) {
    Coordenada imgSize = {size*100, size*70};
    BMP imagen;
    imagen.SetSize(imgSize.x,imgSize.y);
    imprimirAngulo(imgSize,(&imagen),tablero, getMap());
    imagen.WriteToFile("Partida.bmp");
}

int main(){
    string cortar = "",ficha = "";
    bool seguir = false;
    int size = 20;
    coordenadas coordenadaFichaActual = {-1,-1,-1};
    Tablero<Celda*>* tablero = new Tablero<Celda*>(size, size, size);

    Lista<Jugador*>* listaJugadores = new Lista<Jugador*>();        //agregado
    int cantJugadores;
    int r = 0, g = 0, b = 0;
    string tipoDeMapa = "";
    char movimiento;
    coordenadas ubicacionMina;

    solicitarJugadores(&cantJugadores);

    string* nombreJugadores = new string[cantJugadores];
    int* valoresR = new int[cantJugadores];
    int* valoresG = new int[cantJugadores];
    int* valoresB = new int[cantJugadores];

    pedirDatosIniciales(cantJugadores, tipoDeMapa, nombreJugadores, valoresR, valoresG ,valoresB);

    pedirMovimiento(&movimiento);
    pedirUbicacionMina(&ubicacionMina, size);

    //para probar
    cout << "\nTipo de mapa ingresado: " << tipoDeMapa;
    cout << "\nMovimiento: " << movimiento;
    cout << "\ncoordenadas: " << ubicacionMina.x << ubicacionMina.y << ubicacionMina.z;
    for(int i=0; i<cantJugadores; i++){
        cout << "\nnombre jugador " << i+1 << ": " << nombreJugadores[i] << "\n";
        cout << "colores: " << valoresR[i] << valoresG[i] << valoresB[i];
    }

    //cargarJuego(listaJugadores);

    delete[] valoresR;
    delete[] valoresG;
    delete[] valoresB;
    delete[] nombreJugadores;

    delete tablero;
    delete listaJugadores;
    return 0;
}