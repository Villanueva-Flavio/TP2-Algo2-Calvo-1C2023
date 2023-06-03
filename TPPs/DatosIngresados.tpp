//#include "./Headers/DatosIngresados.h"
#include<iostream>
#include <string>

using namespace std; //

void solicitarJugadores(int* cantJugadores){
    char comenzar = ' ';

    cout << "------------------Batala Digital------------------\n\nPresiona cualquier tecla para comenzar: ";
    cin >> comenzar;

    //system("clear");

    cout << "Ingrese la cantidad de jugadores: ";
    cin >> *cantJugadores;

    while ((*cantJugadores) <= 0 || (*cantJugadores) >= 30){       //definir    
        cout << "Ingrese una cantidad valida de jugadores. Numero de jugadores: \n";
        cin >> *cantJugadores;
    }

}

void pedirDatosIniciales(int cantJugadores, string tipoDemapa, std::string* nombreJugadores, int* valoresR, int* valoresG ,int* valoresB){

    cout << "Ingrese el color del jugador" "(ingresar 3 valores entre 0 y 255 inclusive): ";
    
    for (int i = 0; i < cantJugadores; i++) {
        bool nombreValido = false;
        
        while (!nombreValido) {
            cout << "Ingrese el nombre del jugador " << i + 1 << ": ";
            cin >> nombreJugadores[i];

            if (nombreJugadores[i] != "") {
                (nombreValido) = true;
            } else {
                cout << "Nombre inválido. Ingrese un nombre válido.\n";
            }
        }

        cout << "Ingrese el color del jugador " << i + 1 << " (ingresar 3 valores entre 0 y 255 inclusive): ";
        cin >> valoresR[i] >> valoresG[i] >> valoresB[i];
        
        while(valoresR[i] < 0 || valoresR[i] > 255 || valoresG[i] < 0 || valoresG[i] > 255 || valoresB[i] < 0 || valoresB[i] > 255){
            cout << "Ingrese un color valido (ingresar 3 valores entre 0 y 255 inclusive): ";
            cin >> valoresR[i] >> valoresG[i] >> valoresB[i];
        }
    }

    //system("clear");
}
