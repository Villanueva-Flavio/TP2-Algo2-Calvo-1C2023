#include<iostream>
#include <string>

using namespace std; //

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

void pedirDatosIniciales(int cantJugadores, string tipoDemapa, std::string* nombreJugadores, int* valoresR, int* valoresG ,int* valoresB){
    
    for (int i = 0; i < cantJugadores; i++) {
        bool nombreValido = false;
        
        while (!nombreValido) {
            cout << "\nIngrese el nombre del jugador " << i + 1 << ": ";
            cin >> nombreJugadores[i];

            if (nombreJugadores[i] != "") {
                (nombreValido) = true;
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
