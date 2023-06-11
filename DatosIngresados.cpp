#include <iostream>
#include <string>
#include "./Headers/DatosIngresados.h"

using namespace std;

const char MOVIMIENTO_ARRIBA = 'w';
const char MOVIMIENTO_IZQUIERDA = 'a';
const char MOVIMIENTO_ABAJO = 's';
const char MOVIMIENTO_DERECHAA = 'd';

void solicitarJugadores(int* cantJugadores){
    char comenzar = ' ';

    cout << "\n--------------------Batala Digital--------------------\n\nPresiona cualquier tecla para comenzar: ";
    cin >> comenzar;

    //system("clear");

    cout << "\nIngrese la cantidad de jugadores: ";
    cin >> *cantJugadores;

    while ((*cantJugadores) <= 0 || (*cantJugadores) >= 30){       //definir    
        cout << "Ingrese una cantidad valida de jugadores: ";
        cin >> *cantJugadores;
    }

}

void pedirDatosIniciales(int cantJugadores, string& tipoDemapa, std::string* nombreJugadores, int* valoresR, int* valoresG ,int* valoresB){
    cout << "\nSeleccione un tipo de mapa. (playa - mar - tierra - desierto - rio - lago)\n(escriba su respuesta): ";
    cin >> tipoDemapa;

    while(tipoDemapa != "playa" && tipoDemapa != "mar" && tipoDemapa != "tierra" && tipoDemapa != "desierto" && tipoDemapa != "rio" && tipoDemapa != "lago"){
        cout << "\nNo se ingrese un tipo de mapa valido.\nSeleccione un tipo de mapa. (playa - mar - tierra - desierto - rio - lago)\n(escriba su respuesta): ";
        cin >> tipoDemapa;
    }

    for (int i = 0; i < cantJugadores; i++) {
        bool nombreValido = false;
        
        while (!nombreValido) {
            cout << "\nIngrese el nombre del jugador " << i + 1 << ": ";
            cin >> nombreJugadores[i];

            if (nombreJugadores[i] != "") {
                nombreValido = true;
            }
        }

        cout << "Ingrese el color del jugador " << i + 1 << " (ingresar 3 valores entre 0 y 255 inclusive): ";
        cin >> valoresR[i] >> valoresG[i] >> valoresB[i];
        
        while(valoresR[i] < 0 || valoresR[i] > 255 || valoresG[i] < 0 || valoresG[i] > 255 || valoresB[i] < 0 || valoresB[i] > 255){
            cout << "Ingrese un color valido (ingresar 3 valores entre 0 y 255 inclusive): ";
            cin >> valoresR[i] >> valoresG[i] >> valoresB[i];
        }
    }
}

void pedirMovimiento(char* movimiento){
    bool movimientoValido = false;

    cout << "\nIngrese un movimiento (w-a-s-d): ";
    cin >> *movimiento;

    while(*movimiento != MOVIMIENTO_ARRIBA && *movimiento != MOVIMIENTO_IZQUIERDA && *movimiento != MOVIMIENTO_ABAJO && *movimiento != MOVIMIENTO_DERECHAA) {
        cout << "No se ingrese un movimiento valido.\nIngrese un movimiento (w-a-s-d): ";
        cin >> *movimiento;
    }
}

void pedirUbicacionMina(coordenadas* ubicacionMina, int size){
    cout << "\nIngrese las coordenadas x y z: ";
    cin >> ubicacionMina->x >> ubicacionMina->y >> ubicacionMina->z;

    while(ubicacionMina->x < 0 || ubicacionMina->x > size || ubicacionMina->y < 0 || ubicacionMina->y > size || ubicacionMina->z < 0 || ubicacionMina->z > size){
        cout << "No se ingresaron 3 valores validos.\nIngrese las coordenadas x y z: ";
        cin >> ubicacionMina->x >> ubicacionMina->y >> ubicacionMina->z;
    }
}