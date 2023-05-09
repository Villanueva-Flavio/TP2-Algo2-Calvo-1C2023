#include <iostream>
#include "jugador.h"

int main()
{

    int num_de_pjs = -1;

    std::cout << "Ingrese el num de jugadores: ";
    std::cin >> num_de_pjs;

    Jugador *vectorJugadores = new Jugador[num_de_pjs];

    vectorJugadores[0].setNumMinas(3);

    int estadoMina = vectorJugadores[0].minas[0].getEstado();
    std::cout<<"Estado de mina 0 del pj 0: " << estadoMina;

    std::cout<<"\n\nSe coloca la mina 0 del pj 0";

    vectorJugadores[0].minas[0].explotar();
    estadoMina = vectorJugadores[0].minas[0].getEstado();

    std::cout<<"\nEstado de mina 0 del jugador 0: " << estadoMina << std::endl;

    delete[] vectorJugadores;

    return 0;
}