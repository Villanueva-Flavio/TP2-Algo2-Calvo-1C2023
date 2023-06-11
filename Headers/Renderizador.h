#ifndef __RENDERIZADOR_H__
#define __RENDERIZADOR_H__

#include <map>
#include "Celda.h"
#include "../EasyBMP/EasyBMP.h"
#define IZQUIERDA 0
#define DERECHA 1
#define ATRAS 2
struct Coordenada{int x; int y; int z;};
struct CoordenadaDouble{double x; double y; double z;};

typedef std::map<int, RGBApixel> MapaColores;
typedef Tablero<Celda*> Mapa;

MapaColores getMap();

RGBApixel getColor(Celda celda, MapaColores colores);

void imprimirBMP(Coordenada imgSize, BMP* image, Mapa* tablero, MapaColores colores);

#endif