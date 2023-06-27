#ifndef __RENDERIZADOR_H__
#define __RENDERIZADOR_H__

#include <map>
#include "Celda.h"
#include "EasyBMP/EasyBMP.h"
#include "Coordenadas.h"
#include "CoordenadasDouble.h"

#define IZQUIERDA 0
#define DERECHA 1
#define ATRAS 2


RGBApixel codigoColorSegunCelda(Capa capaCelda);

bool capaExiste(Capa capaCelda);

double gradosARadianes(double grados);

void getAngulos(double angulos[6], int lado);

void aplicarProyeccionIsometrica(CoordenadaDouble* pixel, int lado);

bool coloresSonIguales(RGBApixel color1, RGBApixel color2);

bool colorEnRango(RGBApixel color);

bool pixelEnRango(int px, int py, Coordenada imgSize);

//bool colorDisponible(RGBApixel color, MapaColores mapa);

//void setPlayerColor(RGBApixel* color, int jugador, MapaColores& mapa);

int pixelSizeGet(RGBApixel color);

bool pixelSizeEnRango(Coordenada pixelPos, Coordenada imgSize);

void pintarEntidad(BMP* image, Coordenada pixelPos, RGBApixel color, Coordenada imgSize);

Coordenada getPixelOffset(int lado, int size);

RGBApixel getColor(Celda celda);

void imprimirBMP(Coordenada imgSize, BMP* image, Tablero<Celda*>* tablero, int jugador);

#endif