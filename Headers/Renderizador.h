#ifndef __RENDERIZADOR_H__
#define __RENDERIZADOR_H__

#include <map>
#include "Celda.h"
#include "../EasyBMP/EasyBMP.h"
#include "Structs/CoordenadaDouble.h"
#include "Structs/Coordenadas.h"

#define IZQUIERDA 0
#define DERECHA 1
#define ATRAS 2

typedef std::map<int, RGBApixel> MapaColores;
typedef Tablero<Celda*> Mapa;

MapaColores getMap();

double gradosARadianes(double grados);

void getAngulos(double angulos[6], int lado);

void aplicarProyeccionIsometrica(CoordenadaDouble* pixel, int lado);

bool coloresSonIguales(RGBApixel color1, RGBApixel color2);

bool colorEnRango(RGBApixel color);

bool pixelEnRango(int px, int py, coordenadas imgSize);

bool colorDisponible(RGBApixel color, MapaColores mapa);

void setPlayerColor(RGBApixel* color, int jugador, MapaColores& mapa);

int pixelSizeGet(RGBApixel color);

bool pixelSizeEnRango(coordenadas pixelPos, coordenadas imgSize);

void pintarEntidad(BMP* image, coordenadas pixelPos, RGBApixel color, coordenadas imgSize);

coordenadas getPixelOffset(int lado, int size);

RGBApixel getColor(Celda celda, MapaColores colores);

void imprimirAngulo(coordenadas imgSize, BMP* image, Mapa* tablero, MapaColores colores);

#endif