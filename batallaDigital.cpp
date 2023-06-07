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



