#ifndef __RENDERIZADOR_H__
#define __RENDERIZADOR_H__

#include <map>
#include "celda.h"
#include "../EasyBMP/EasyBMP.h"
#define IZQUIERDA 0
#define DERECHA 1
#define ATRAS 2
struct Coordenada{int x; int y; int z;};
struct CoordenadaDouble{double x; double y; double z;};

typedef std::map<int, RGBApixel> MapaColores;
typedef Tablero<Celda*> Mapa;

MapaColores getMap();

double gradosARadianes(double grados);

void getAngulos(double angulos[6], int lado);

void aplicarProyeccionIsometrica(CoordenadaDouble* pixel, int lado);

bool coloresSonIguales(RGBApixel color1, RGBApixel color2);

bool colorEnRango(RGBApixel color);

bool pixelEnRango(int px, int py, Coordenada imgSize);

bool colorDisponible(RGBApixel color, MapaColores mapa);

void setPlayerColor(RGBApixel* color, int jugador, MapaColores& mapa);

int pixelSizeGet(RGBApixel color);

bool pixelSizeEnRango(Coordenada pixelPos, Coordenada imgSize);

void pintarEntidad(BMP* image, Coordenada pixelPos, RGBApixel color, Coordenada imgSize);

Coordenada getPixelOffset(int lado, int size);

RGBApixel getColor(Celda celda, MapaColores colores);

void imprimirAngulo(Coordenada imgSize, BMP* image, Mapa* tablero, MapaColores colores);

#endif